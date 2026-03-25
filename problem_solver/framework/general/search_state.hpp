#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "state.hpp"
#include "node.hpp"
#include "frontier.hpp"
#include "../libraries/type.hpp"

template <typename T_Cost, typename T_State, typename T_Solution, typename T_Problem>
class SearchState {
    public:
        int iter = 0;
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, T_State>;
        virtual T_Solution search_solution(const T_Problem &problem) = 0;

        string vector_to_string(const vector<state_type>& vec) {
            string result = "";
            for (const state_type& state : vec){
                result += to_string(state.value) + " ";
            }
            return result;
        }

        int get_iter() {
            return this->iter;
        }
};