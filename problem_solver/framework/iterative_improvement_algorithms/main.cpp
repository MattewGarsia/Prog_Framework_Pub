#include <iostream>
#include <string>
#include "search_state_successor.hpp"
#include "../general/problem.hpp"
#include "../problems/iterative_improvement_problem/chess_problem.hpp"
#include "../problems/iterative_improvement_problem/chess_operator.hpp"
#include "../iterative_improvement_algorithms/hill_climbing.hpp"
#include "../iterative_improvement_algorithms/steepest.hpp"
#include "../iterative_improvement_algorithms/local_beam.hpp"
#include "../iterative_improvement_algorithms/simulating_annealing.hpp"
#include "../iterative_improvement_algorithms/genetic_algorithm.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

template<typename F>
double measureMs(F&& f) {
    auto t0 = chrono::high_resolution_clock::now();
    f();
    return chrono::duration<double, milli>(
        chrono::high_resolution_clock::now() - t0).count();
}

// Ricostruisce un ChessState dal name restituito dagli algoritmi
// che ritornano string (SA, Local_Beam, Genetic)
ChessState stateFromName(const string& name, int N) {
    vector<int> board;
    stringstream ss(name);
    string tok;
    while (getline(ss, tok, ','))
        if (!tok.empty()) board.push_back(stoi(tok));
    return ChessState(board);
}

int main() {
    const int N = 4;
    cout << "N-Queens  N=" << N << "\n";
    cout << string(40, '=') << "\n\n";

    #if 1
    {
        ChessProblem prob(N, /*k=*/1, /*seed=*/42);
        Hill_Climbing<int, ChessState> hc;
        ChessState sol = ChessState(vector<int>(N, 0));
        double ms = measureMs([&]{ sol = hc.search_solution(prob); });

        cout << "[Hill Climbing]\n"
             << "  Conflitti : " << sol.heuristic << "\n"
             << "  Valida    : " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "  Tempo     : " << fixed << setprecision(2) << ms << " ms\n";
        if (sol.heuristic == 0) sol.print();
        cout << "\n";
    }
    #endif

    // ── Steepest Ascent ───────────────────────────────────────
    #if 1
    {
        ChessProblem prob(N, 1, 42);
        Steepest<int, ChessState> st;
        ChessState sol = ChessState(vector<int>(N, 0));
        double ms = measureMs([&]{ sol = st.search_solution(prob); });

        cout << "[Steepest Ascent]\n"
             << "  Conflitti : " << sol.heuristic << "\n"
             << "  Valida    : " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "  Tempo     : " << fixed << setprecision(2) << ms << " ms\n";
        if (sol.heuristic == 0) sol.print();
        cout << "\n";
    }
    #endif

    // ── Simulated Annealing ───────────────────────────────────
    #if 1
    {
        ChessProblem prob(N, 1, 42);
        Simulating_Annealing<int, ChessState> sa;
        string sol_name;
        double ms = measureMs([&]{ sol_name = sa.search_solution(prob); });
        ChessState sol = stateFromName(sol_name, N);

        cout << "[Simulated Annealing]\n"
             << "  Conflitti : " << sol.heuristic << "\n"
             << "  Valida    : " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "  Tempo     : " << fixed << setprecision(2) << ms << " ms\n";
        if (sol.heuristic == 0) sol.print();
        cout << "\n";
    }
    #endif

    // ── Local Beam ────────────────────────────────────────────
    #if 1
    {
        ChessProblem prob(N, /*k=*/5, 42);
        Local_Beam<int, ChessState> lb(5);
        string sol_name;
        double ms = measureMs([&]{ sol_name = lb.search_solution(prob); });
        ChessState sol = stateFromName(sol_name, N);

        cout << "[Local Beam  k=5]\n"
             << "  Conflitti : " << sol.heuristic << "\n"
             << "  Valida    : " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "  Tempo     : " << fixed << setprecision(2) << ms << " ms\n";
        if (sol.heuristic == 0) sol.print();
        cout << "\n";
    }
    #endif

    // ── Genetic Algorithm ─────────────────────────────────────
    #if 1
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

        cout << "[Genetic Algorithm  pop=10]\n"
             << "  Conflitti : " << sol.heuristic << "\n"
             << "  Valida    : " << (sol.heuristic == 0 ? "SI" : "NO") << "\n"
             << "  Tempo     : " << fixed << setprecision(2) << ms << " ms\n";
        if (sol.heuristic == 0) sol.print();
        cout << "\n";
    }
    #endif
    return 0;
}