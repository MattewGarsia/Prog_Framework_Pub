#pragma once
#include "state.hpp"
#include "node.hpp"
using namespace std;

class Compare_G_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            return a.cost > b.cost;
        }
};

class Compare_H_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            //cout<<"H Cost, heuristic: "<<a.current_state.heuristic<<", "<<b.current_state.heuristic<<endl;
            return a.current_state.heuristic > b.current_state.heuristic;
        }
};

class Compare_F_Cost {
    public:
        template<typename T_Cost, typename T_State>
        bool operator()(const Node<T_Cost, T_State>& a, const Node<T_Cost, T_State>& b) const {
            //cout<<"F Cost, heuristic: "<<a.current_state.heuristic<<", "<<b.current_state.heuristic<<endl;
            Node<T_Cost, T_State>* parent_a = a.parent;
            Node<T_Cost, T_State>* parent_b = b.parent;
            while (parent_a != nullptr){
                //cout<<"Parent: "<<parent_a.current_state.heuristic<<endl;
                a.cost += parent_a->cost;
                parent_a = parent_a->parent;
            }
            while (parent_b != nullptr){
                //cout<<"Parent: "<<parent_b.current_state.heuristic<<endl;
                b.cost += parent_b->cost;
                parent_b = parent_b->parent;
            }

            T_Cost f_a = a.cost + a.current_state.heuristic;
            T_Cost f_b = b.cost + b.current_state.heuristic;
            return f_a > f_b;
        }
};