#pragma once
#include "local_search.hpp"
#include "../libraries/type.hpp"
#include "../libraries/random.hpp"
#include "../iterative_improvement_algorithms/problem_curr_pop.hpp"
#include <stdexcept>
using namespace std;

template <typename T_Cost, typename T_State>
class Steepest : public Local_Search<T_Cost, T_State, T_State>{
    public:
        using state_type = T_State;
        using node_type = General_Node<T_Cost, state_type>;
        using problem_type = typename Local_Search<T_Cost, state_type, state_type>::problem_type;
        Steepest() : Local_Search<T_Cost, state_type, state_type>(){
            
        }

        T_State search_solution(const typename Local_Search<T_Cost, state_type, state_type>::problem_type& generic_problem) override {
            auto problem = dynamic_cast<const problem_type*>(&generic_problem);
            if (!problem) {
                throw invalid_argument("Steepest richiede un Problem_popul compatibile");
            }

            node_type current_node(problem->initial_node->current_state);
            while (true) {
                state_type neighbor = problem->get_best_neighbor(current_node.current_state);
                if (neighbor.heuristic >= current_node.current_state.heuristic) {
                    //return current_node.current_state;
                    current_node = node_type(problem->get_random_state(), nullptr, current_node.cost, current_node.depth + 1);
                }
                else{
                    current_node = node_type(neighbor, nullptr, current_node.cost, current_node.depth + 1);
                }

                if (current_node.current_state.heuristic == 0) {
                    return current_node.current_state;
                }
            }
        }
};