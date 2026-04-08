#pragma once
#include "local_search.hpp"
#include "../libraries/type.hpp"
#include "../libraries/random.hpp"
#include "../iterative_improvement_algorithms/problem_curr_pop.hpp"
using namespace std;

#define MAX_NUMBER_OF_ATTEMPTS 100

template <typename T_Cost, typename T_State>
class Hill_Climbing : public Local_Search<T_Cost, T_State, T_State>{
    public:
        using state_type = T_State;
        using node_type = General_Node<T_Cost, state_type>;
        using problem_type = typename Local_Search<T_Cost, state_type, state_type>::problem_type;
        bool move_found = false;
        Hill_Climbing() : Local_Search<T_Cost, state_type, state_type>(){}

        T_State search_solution(const problem_type& generic_problem) override {
            auto problem = dynamic_cast<const problem_type*>(&generic_problem);
            if (!problem) {
                throw invalid_argument("Hill_Climbing richiede un Problem_popul compatibile");
            }

            node_type current_node(problem->initial_node->current_state);
            while (true) {
                move_found = false;
                int attempts = 0;
                while (!move_found && attempts < MAX_NUMBER_OF_ATTEMPTS) {
                    state_type next_state = problem->get_random_neighbor(current_node.current_state);
                    //cout<<"Current state: "<<current_node.current_state.name<<", heuristic: "<<current_node.current_state.heuristic<<endl;
                    //cout<<"Next state: "<<next_state.name<<", heuristic: "<<next_state.heuristic<<endl;
                    if (next_state.heuristic < current_node.current_state.heuristic) {
                        current_node = node_type(next_state, nullptr, current_node.cost, current_node.depth + 1);
                        move_found = true;
                    }
                    attempts++;
                }
                if (!move_found) {
                    current_node = node_type(problem->get_random_state(), nullptr, current_node.cost, current_node.depth + 1);
                }
                if (current_node.current_state.heuristic == 0) {
                    return current_node.current_state;
                }
            }
        }
};