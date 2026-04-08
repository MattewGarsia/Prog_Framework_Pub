#pragma once
#include <vector>
#include <map>
using namespace std;

template<typename T_Var, typename T_Val>
class Constraint {
    public:
        virtual bool is_satisfied(const map<T_Var, T_Val>& variables) const = 0;
        virtual vector<T_Var> get_variables() const = 0;
};