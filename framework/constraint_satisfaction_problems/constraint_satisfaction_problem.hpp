#pragma once
#include <vector>
#include <map>
#include "variable.hpp"
#include "constraint.hpp"
using namespace std;

template<typename T_Var, typename T_Domain>
class Constraint_Satisfaction_Problems {
    public:
        vector<Variable<T_Domain>> variables;
        vector<Constraint<T_Var, T_Domain>> constraints;

        void add_Constraint(Constraint<T_Var, T_Domain> c) {
            constraints.push_back(c);
        }
        
        void add_Variable(Variable<T_Domain> v) {
            variables.push_back(v);
        }
        
        bool is_consistent(const map<T_Var, T_Domain>& assignment) const {
            for (const auto& constraint : constraints) {
                if (!constraint.is_satisfied(assignment)) {
                    return false;
                }
            }
            return true;
        }
};