#pragma once

#include "../general/search_state.hpp"
#include "variable.hpp"
#include "constraint_satisfaction_problem.hpp"
using namespace std;

template <typename T_Domain>
class Constraint_Satisfaction_Solver : public SearchState<double, Variable, map<Variable, T_Domain>, 
                                                        Constraint_Satisfaction_Problem<T_Domain>> {
    public:
        Constraint_Satisfaction_Solver();

};