#pragma once
#include "search_state_successor.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class Local_Beam : public SearchStateSuccessor<T_Cost, T_State>{
    public:
        using base_type = SearchStateSuccessor<T_Cost, T_State>;
        using state_type = typename base_type::state_type;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = Types::problem_type<T_Cost, state_type>;
        Local_Beam(int _k = 1) : SearchStateSuccessor<T_Cost, state_type>(_k){

        }

        string search_solution(const problem_type& problem) override {
            const auto& pop_problem = static_cast<const Problem_popul<T_Cost, state_type>&>(problem);
            vector<state_type> current_pop = pop_problem.current_population;

            while (true) {
                this->successors.clear();
                for (const state_type& state : current_pop) {
                    vector<typename node_type::action_type*> actions = problem.get_actions(state);
                    for (auto* action : actions) {
                        state_type neighbor = problem.get_result(state, *action);
                        if (neighbor.is_objective())
                            return neighbor.name;
                        this->successors.push_back(neighbor);
                    }
                }
                current_pop = this->get_best_k_successors();
            }
        }
};