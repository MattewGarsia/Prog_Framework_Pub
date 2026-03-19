#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "state.hpp"
#include "node.hpp"
#include "frontier.hpp"
#include "../libraries/type.hpp"

template <typename T_Cost, typename T_State, typename T_Solution>
class SearchState {
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, T_State>;
        using problem_type = Types::problem_type<T_Cost, T_State>;

        virtual T_Solution search_solution(const problem_type &problem) = 0;

        string vector_to_string(const vector<state_type>& vec) {
            string result = "";
            for (const state_type& state : vec){
                result += to_string(state.value) + " ";
            }
            return result;
        }

        void print_iteration(node_type node, int iter, bool is_child = false){
            #define PRINT_ON 0


            #if !PRINT_ON
            (void)node;
            (void)iter;
            (void)is_child;
            #endif

            #if PRINT_ON
            string result = "";
            if (is_child){
                result += "child: "+ to_string(node.current_state.name) + ", cost: " + to_string(node.cost);
            } else {
                result += "node: "+ to_string(node.current_state.name) + ", cost: " + to_string(node.cost);
            }
            result += "| frontier: "+ this->frontier->frontier_to_string();
            result += "| explored: "+ this->vector_to_string(explored);
            result += "| iteration: " + to_string(iter);

            result+="\n";
            cout<<result;
            #endif
        }

        int get_iter() {
            return this->iter;
        }
};