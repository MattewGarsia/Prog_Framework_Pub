#pragma once
#include "../general/search_state.hpp"
#include "../libraries/type.hpp"
#include "../libraries/random.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class Hill_Climbing : public SearchState<T_Cost, T_State, T_State>{
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = Types::problem_type<T_Cost, state_type>;
        bool move_found = false;
        Hill_Climbing() : SearchState<T_Cost, state_type, state_type>(){
            
        }

        T_State search_solution(const problem_type& problem) override {
            node_type current_node(problem.initial_node->current_state, nullptr, nullptr);
            while (true) {
                move_found = false;
                vector<typename node_type::action_type*> actions = problem.get_actions(current_node.current_state);
                while (!move_found && !actions.empty()) {
                    int i = random_int(0, static_cast<int>(actions.size()) - 1);
                    state_type next_state = problem.get_result(current_node.current_state, *actions[i]);
                    actions.erase(actions.begin() + i); // Rimuove l'azione già considerata
                    //cout<<"Current state: "<<current_node.current_state.name<<", heuristic: "<<current_node.current_state.heuristic<<endl;
                    //cout<<"Next state: "<<next_state.name<<", heuristic: "<<next_state.heuristic<<endl;
                    if (next_state.heuristic < current_node.current_state.heuristic) {
                        current_node = node_type(next_state, actions[i], new node_type(current_node));
                        move_found = true;
                    }
                }
                if (!move_found) {
                    return current_node.current_state;
                }
            }
        }
};