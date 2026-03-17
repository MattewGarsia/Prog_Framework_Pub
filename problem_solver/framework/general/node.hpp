#pragma once
#include "state.hpp"
#include "action.hpp"
#include <ostream>
using namespace std;

template<typename T_Type_Cost, typename T_Type_State>
class Node
{
    public: 
        using node_type = Node<T_Type_Cost, T_Type_State>;
        using action_type = Action<T_Type_Cost, T_Type_State>;

        T_Type_State current_state;
        action_type* action = nullptr;
        node_type* parent_node = nullptr;
        int depth = 0;
        T_Type_Cost cost = 0;

        Node() = default;

        Node(T_Type_State state_in, action_type* action_in = nullptr, node_type* dad_in = nullptr): 
            current_state(state_in), action(action_in), parent_node(dad_in) {
            
            if(parent_node != nullptr){
                this->cost = parent_node->cost + (action_in != nullptr ? action_in->getCost() : 0);
                this->depth = parent_node->depth + 1;
            }else{
                this->depth = 0;
                this->cost = 0;
            }
        }

};

template<typename T_Type_Cost, typename T_Type_State>
ostream& operator<<(ostream& os, const Node<T_Type_Cost, T_Type_State>& node) {
    os << node.current_state.name;
    return os;
}