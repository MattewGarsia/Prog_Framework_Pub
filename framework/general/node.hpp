#pragma once
#include "state.hpp"
#include "action.hpp"
#include "general_node.hpp"
#include <ostream>
using namespace std;

template<typename T_Cost, typename T_State>
class Node : public General_Node<T_Cost, T_State>
{
    public: 
        using base_type = General_Node<T_Cost, T_State>;
        using node_type = Node<T_Cost, T_State>;
        using action_type = Action<T_Cost, T_State>;

        node_type* parent_node = nullptr;

        Node() = default;

        Node(T_State state_in, const action_type* action_in = nullptr, node_type* parent = nullptr)
            : base_type(state_in, action_in, 0, T_Cost{}), parent_node(parent) {

            if (this->parent_node != nullptr) {
                this->cost = this->parent_node->cost + (this->action != nullptr ? this->action->getCost() : 0);
                this->depth = this->parent_node->depth + 1;
            } else {
                this->depth = 0;
                this->cost = 0;
            }
        }
};

template<typename T_Cost, typename T_State>
ostream& operator<<(ostream& os, const Node<T_Cost, T_State>& node) {
    os << node.current_state.name;
    return os;
}
