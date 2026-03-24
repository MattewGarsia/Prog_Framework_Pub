
#include <iostream>
#include <string>
#include <iomanip>
#include "space_state_expl_1.hpp"
#include "space_state_expl_2.hpp"
#include "../../general/problem.hpp"
#include "../../libraries/timing.hpp"
#include "../../search_tree_algorithms/search_state_explorer.hpp"
#include "../../search_tree_algorithms/bfs.hpp"
#include "../../search_tree_algorithms/dfs.hpp"
#include "../../search_tree_algorithms/min_cost.hpp"
#include "../../search_tree_algorithms/best_first_greedy.hpp"
#include "../../search_tree_algorithms/a_star.hpp"
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

template <typename Problem>
void run(const string& expl_name, const Problem& problem) {
    if (expl_name == "dfs") {
        dfs<double> explorer;
        auto sol = explorer.search_solution(problem);
        TimingResult timing = measure_time<dfs<double>>(problem);
        cout << expl_name << endl;
        print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
    } else if (expl_name == "bfs") {
        bfs<double> explorer;
        auto sol = explorer.search_solution(problem);
        TimingResult timing = measure_time<bfs<double>>(problem);
        cout << expl_name << endl;
        print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
    } else if (expl_name == "MinCost") {
        min_cost<double> explorer;
        auto sol = explorer.search_solution(problem);
        TimingResult timing = measure_time<min_cost<double>>(problem);
        cout << expl_name << endl;
        print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
    } else if (expl_name == "Greedy") {
        best_first_greedy<double> explorer;
        auto sol = explorer.search_solution(problem);
        TimingResult timing = measure_time<best_first_greedy<double>>(problem);
        cout << expl_name << endl;
        print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
    } else if (expl_name == "A*") {
        a_star<double> explorer;
        auto sol = explorer.search_solution(problem);
        TimingResult timing = measure_time<a_star<double>>(problem);
        cout << expl_name << endl;
        print_solution(sol, explorer.get_iter(), timing.avg_ms, timing.repetitions);
    }else if (expl_name == "All") {
        cout << "Running all explorers...\n\n";
        run("dfs", problem);
        run("bfs", problem);
        run("MinCost", problem);
        run("Greedy", problem);
        run("A*", problem);
    } else {
        cerr << "Invalid explorer name." << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <explorer_name>" << " <problem_name>"  <<endl;
        return 1;
    }

    string explorer_name = argv[1];
    string problem_name = argv[2];

    if (problem_name == "problem1"){
        Space_State_Expl_1 problem1;
        run(explorer_name, problem1);
    }
    else if (problem_name == "problem2"){
        Space_State_Expl_2 problem2;
        run(explorer_name, problem2);
    }
    else if (problem_name == "All"){
        Space_State_Expl_1 problem1;
        Space_State_Expl_2 problem2;
        cout << "Running all explorers on problem1...\n\n";
        run("All", problem1);
        cout << "Running all explorers on problem2...\n\n";
        run("All", problem2);
    }
    else {
        cerr << "Invalid problem name. Use 'problem1' or 'problem2'." <<endl;
        return 1;
    }
}