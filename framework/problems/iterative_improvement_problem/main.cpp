#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

#include "chess_problem.hpp"
#include "chess_operator.hpp"

#include "../../iterative_improvement_algorithms/search_state_successor.hpp"
#include "../../iterative_improvement_algorithms/hill_climbing.hpp"
#include "../../iterative_improvement_algorithms/steepest.hpp"
#include "../../iterative_improvement_algorithms/simulating_annealing.hpp"
#include "../../iterative_improvement_algorithms/genetic_algorithm.hpp"

using namespace std;

template<typename F>
double measureMs(F&& f) {
    auto t0 = chrono::high_resolution_clock::now();
    f();
    return chrono::duration<double, milli>(
        chrono::high_resolution_clock::now() - t0).count();
}

ChessState stateFromName(const string& name) {
    vector<int> board;
    stringstream ss(name);
    string tok;
    while (getline(ss, tok, ','))
        if (!tok.empty()) board.push_back(stoi(tok));
    return ChessState(board);
}

void print_sol(const ChessState& sol, string name, double ms) {
     cout << "[" << name << "]\n"
             << "Conflitti: " << sol.heuristic << "\n"
             << "Valida: " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "Tempo: " << fixed << setprecision(2) << ms << " ms\n";
    if (sol.heuristic == 0) sol.print();
    cout << "\n";
}

template <typename Problem>
void run(string algo_name, Problem& prob, int N){
    ChessState sol = ChessState(vector<int>(N, 0));
    double ms;

    if (algo_name == "Hill"){
        Hill_Climbing<int, ChessState> hc;
        ms = measureMs([&]{ sol = hc.search_solution(prob); });
    }

    else if (algo_name == "Steepest"){
        Steepest<int, ChessState> st;
        ms = measureMs([&]{ sol = st.search_solution(prob); });
    }

    else if (algo_name == "Simulation_Annealing")
    {
        Simulating_Annealing<int, ChessState> sa;
        string sol_name;
        ms = measureMs([&]{ sol_name = sa.search_solution(prob); });
        sol = stateFromName(sol_name);
    }
    else if (algo_name == "All"){
        run("Hill", prob, N);
        run("Steepest", prob, N);
        run("Simulation_Annealing", prob, N);
        return;
    }
    else{
        cout << "Algoritmo sconosciuto: " << algo_name << "\n";
        return;
    }

    print_sol(sol, algo_name, ms);
}

int main(int argc, char* argv[]) {
    string algorithm_name;
    int N = 4;
    if (argc > 2) {
        algorithm_name = argv[1];
        N = stoi(argv[2]);
    } else {
        cout << "Nessun algoritmo specificato\n\n";
        return 1;
    }

    ChessProblem prob(N, 1, 42);
    cout << "N-Queens  N=" << N << "\n";
    cout << string(40, '=') << "\n\n";

    run(algorithm_name, prob, N);
    

    #if 0
    {
        ChessProblem prob(N, /*k=*/10, 42);
        ChessOperator chess_operator;
        Genetic_Algorithm<int, ChessState> ga(&chess_operator,
                                              200,
                                              0.05,
                                              10);
        string sol_name;
        double ms = measureMs([&]{ sol_name = ga.search_solution(prob); });
        ChessState sol = stateFromName(sol_name, N);
        print_sol(sol, "Genetic Algorithm", ms);
    }
    #endif

    return 0;
}