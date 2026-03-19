#pragma once
#include "state.hpp"
#include "node.hpp"
using namespace std;

class Compare_G_Cost {
    public:
        template<typename T_Type_Cost, typename T_Type_State>
        bool operator()(const Node<T_Type_Cost, T_Type_State>& a, const Node<T_Type_Cost, T_Type_State>& b) const {
            return a.cost > b.cost;
        }
};

class Compare_H_Cost {
    public:
        template<typename T_Type_Cost, typename T_Type_State>
        bool operator()(const Node<T_Type_Cost, T_Type_State>& a, const Node<T_Type_Cost, T_Type_State>& b) const {
            //cout<<"H Cost, heuristic: "<<a.current_state.heuristic<<", "<<b.current_state.heuristic<<endl;
            return a.current_state.heuristic > b.current_state.heuristic;
        }
};

class Compare_F_Cost {
    public:
        template<typename T_Type_Cost, typename T_Type_State>
        bool operator()(const Node<T_Type_Cost, T_Type_State>& a, const Node<T_Type_Cost, T_Type_State>& b) const {
            //cout<<"F Cost, heuristic: "<<a.current_state.heuristic<<", "<<b.current_state.heuristic<<endl;
            T_Type_Cost f_a = a.cost + a.current_state.heuristic;
            T_Type_Cost f_b = b.cost + b.current_state.heuristic;
            return f_a > f_b;
        }
};


class Compare_Quality{
    public:
        template<typename T_Quality>
        bool operator()(const T_Quality& a, const T_Quality& b) const {
            return a > b;
        }
};