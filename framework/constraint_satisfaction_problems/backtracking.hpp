#pragma once

#include <map>
#include "constraint_satisfaction_problem.hpp"
#include "constraint.hpp"
#include "variable.hpp"
using namespace std;

template<typename T_Domain>
class Backtracking {
    public:
        virtual void evolution_policy(map<Variable, T_Domain>& ass, Variable var, T_Domain value) = 0;
        virtual Variable get_var_not_occur(map<Variable, T_Domain>& ass) = 0;

        map<Variable, T_Domain> search_solution(Problem csp, map<Variable, T_Domain>& ass){
            return solve(csp, ass);
        }

        map<Variable, T_Domain> solve(Problem csp, map<Variable, T_Domain>& ass){
            if(ass.is_complete()) return ass;

            Variable var = get_var_not_occur(ass);
            for (T_Domain value : var.get_domain()) {
                if (csp.is_consistent(ass)) {
                    ass.add(var, value);
                    evolution_policy(ass, var, value);
                }
            }
            return map<Variable, T_Domain>();
        }
};