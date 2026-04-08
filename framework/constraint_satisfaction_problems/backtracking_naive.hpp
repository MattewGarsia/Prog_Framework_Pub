#pragma once

#include <map>
#include "constraint_satisfaction_problem.hpp"
#include "backtracking.hpp"
#include "constraint.hpp"
#include "variable.hpp"
using namespace std;

template<typename T_Domain>
class Backtracking_Naive : public Backtracking<T_Domain> {
    public:
        evolution_policy(map<Variable, T_Domain>& ass, Variable var, T_Domain value){
            
        }
};