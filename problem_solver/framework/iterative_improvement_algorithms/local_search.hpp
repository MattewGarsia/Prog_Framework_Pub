#pragma once

#include "../general/search_state.hpp"
#include "problem_curr_pop.hpp"
using namespace std;

template <typename T_Cost, typename T_State, typename T_Solution>
class Local_Search : public SearchState<T_Cost, T_State, T_Solution, Problem_popul<T_Cost, T_State>>{
    public:
        using problem_type = Problem_popul<T_Cost, T_State>;
    virtual void stopping_policy() {}
    virtual void evolving_pop_policy() {}
};