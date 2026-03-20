#pragma once
#include "../general/search_state.hpp"
#include "../libraries/type.hpp"
#include "../libraries/random.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class Steepest : public SearchState<T_Cost, T_State, T_State>{
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = Types::problem_type<T_Cost, state_type>;
        Steepest() : SearchState<T_Cost, T_State, T_State>(){
            
        }

        T_State search_solution(const problem_type& problem) override {
            node_type current_node(problem.initial_node->current_state, nullptr, nullptr);
            while (true) {
                vector<typename node_type::action_type*> actions = problem.get_actions(current_node.current_state);
                if (actions.empty()) {
                    return current_node.current_state;
                }

                int i = random_int(0, static_cast<int>(actions.size()) - 1);
                state_type neighbor = problem.get_result(current_node.current_state, *actions[i]);
                if (neighbor.heuristic >= current_node.current_state.heuristic) {
                    return current_node.current_state;
                }
                current_node = node_type(neighbor, actions[i], new node_type(current_node));
            }
        }
};