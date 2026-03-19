#include <iostream>
#include <string>
#include "search_state_successor.hpp"
#include "../general/problem.hpp"
#include "../graphs/search_state_problem/graphProblem.hpp"
#include "../libraries/timing.hpp"
#include "../libraries/namespace.hpp"
using namespace iterative_improvement_algorithms;
using namespace std;


int test_iterative_improvement_algorithms(){
    #if 1
    HillClimbingAlgorithm<double> hill_climbing_explorer;
    run(hill_climbing_explorer, "Hill Climbing Solution:", problem);
    #endif

    #if 1
    Steepest<double> steepest_explorer;
    run(steepest_explorer, "Steepest Ascent Solution:", problem);
    #endif

    #if 1
    Local_Beam<double> local_beam_explorer(3);
    run(local_beam_explorer, "Local Beam Solution:", problem);
    #endif

    #if 1
    Simulated_Annealing<double> simulated_annealing_explorer(1000, 0.95);
    run(simulated_annealing_explorer, "Simulated Annealing Solution:", problem);
    #endif

    #if 1
    GenerativeAlgorithm<double> genetic_explorer(1000, 0.1);
    run(genetic_explorer, "Genetic Algorithm Solution:", problem);
    #endif
    return 0;
}

template <typename NodeType>
void print_solution(
    const vector<NodeType>& solution,
    int iter,
    double elapsed_ms = 0.0,
    int repetitions = 1) {
    if (!solution.empty()) {
        int final_cost = 0;
        cout << "Solution found! Path: ";
        for (size_t i = 0; i < solution.size(); i++) {
            cout << solution[i].current_state.name;
            if (i + 1 < solution.size()) cout << " -> ";
        }
        final_cost = solution[solution.size() - 1].cost;
        cout << "\nFinal cost: " << final_cost << endl;
        cout << "Iterations: " << iter << endl;
        cout << fixed << setprecision(6);
        cout << "Elapsed time (s): " << (elapsed_ms) << " ms" << endl;
        if (repetitions > 1) {
            cout << "(average over " << repetitions << " runs)" << endl;
        }
        cout.unsetf(ios::floatfield);
        cout<<"\n";
    } else {
        cout << "No solution found.\n\n";
    }
}

template <typename Explorer>
void run(Explorer& explorer, const string& label, const graphProblem& problem) {
    auto sol = explorer.search_solution(problem);
    TimingResult timing = measure_time<Explorer>(problem);
    cout << label << endl;
    print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
}