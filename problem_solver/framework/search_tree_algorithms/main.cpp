
#include <iostream>
#include <string>
#include <iomanip>
#include "search_state_explorer.hpp"
#include "../general/problem.hpp"
#include "../graphs/search_state_problem/graphProblem.hpp"
#include "../libraries/timing.hpp"
#include "../search_tree_algorithms/bfs.hpp"
#include "../search_tree_algorithms/dfs.hpp"
#include "../search_tree_algorithms/min_cost.hpp"
#include "../search_tree_algorithms/best_first_greedy.hpp"
#include "../search_tree_algorithms/a_star.hpp"
using namespace std;

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

int main(){
    graphProblem problem;
    
    #if 1
    dfs<double> dfs_explorer;
    run(dfs_explorer, "DFS Solution:", problem);
    #endif

    #if 1
    bfs<double> bfs_explorer;
    run(bfs_explorer, "BFS Solution:", problem);
    #endif

    #if 1
    min_cost<double> min_cost_explorer;
    run(min_cost_explorer, "Min Cost Solution:", problem);
    #endif

    #if 1
    best_first_greedy<double> greedy_explorer;
    run(greedy_explorer, "Greedy Solution:", problem);
    #endif

    #if 1
    a_star<double> a_star_explorer;
    run(a_star_explorer, "A* Solution:", problem);
    #endif
    return 0;
}