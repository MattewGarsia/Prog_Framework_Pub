#pragma once

#include "../general/solver.hpp"
#include "problem_curr_pop.hpp"
using namespace std;

template <typename T_Cost, typename T_State, typename T_Solution>
class Local_Search : public Solver<T_Cost, T_State, T_Solution, Problem_popul<T_Cost, T_State>>{
    public:
        using problem_type = Problem_popul<T_Cost, T_State>;
        using state_type = T_State;
        using node_type = General_Node<T_Cost, state_type>;
        //using problem_type = typename Local_Search<T_Cost, state_type, state_type>::problem_type;

};
