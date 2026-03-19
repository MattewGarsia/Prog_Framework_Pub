#pragma once
#include "../general/search_state.hpp"
#include "../libraries/type.hpp"
using namespace std;

template <typename T_Cost, typename T_State, typename T_State>
class Hill_Climbing : public SearchState<T_Cost, T_State, T_State>{
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, T_State>;
        using problem_type = Types::problem_type<T_Cost, T_State>;
        bool move_found = false;
        Hill_Climbing() : SearchState(){
            
        }

        T_State search_solution(problem_type& problem)override{
            node_type current_node(problem.initial_node->current_state, nullptr, nullptr);
            while(true){
                move_found = false;
                while (!move_found && !problem.get_actions(current_node.current_state).empty()) {
                    int i = random_range(0, problem.get_actions(current_node.current_state).size() - 1);
                    node_type neighbor = problem.get_result(current_node.current_state, problem.get_actions(current_node.current_state)[i]);
                    if (this->compare_quality(neighbor, current_node)) {
                        current_node = neighbor;
                        move_found = true;
                    }
                }
                if (!move_found) {
                    return this->solution(current_node.state);
                }
            }
        }
};