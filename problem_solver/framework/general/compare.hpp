#pragma once
#include "state.hpp"
#include "node.hpp"
using namespace std;

class Compare_G_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            if ( a.cost == b.cost) {
                return a.current_state.name > b.current_state.name;
            }
            return a.cost > b.cost;
        }
};

class Compare_H_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            //cout<<"H Cost, heuristic: "<<a.current_state.heuristic<<", "<<b.current_state.heuristic<<endl;
            if (a.current_state.heuristic == b.current_state.heuristic) {
                return a.current_state.name > b.current_state.name;
            }
            return a.current_state.heuristic > b.current_state.heuristic;
        }
};

class Compare_F_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            
            T_Cost f_a = a.cost + a.current_state.heuristic;
            T_Cost f_b = b.cost + b.current_state.heuristic;
            if (f_a == f_b) {
                return a.current_state.name > b.current_state.name;
            }
            //cout<<"Node "<<a.current_state.name<<", f: "<<f_a<<endl;
            //cout<<"Node "<<b.current_state.name<<", f: "<<f_b<<endl;
            return f_a > f_b;
        }
};