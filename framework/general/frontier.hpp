#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "node.hpp"

using namespace std;

template<typename T_Cost, typename T_State,  typename T_Queue_Struct>
class Frontier {
    public:
        using node_type = Node<T_Cost, T_State>;

        T_Queue_Struct nodes;

        Frontier() = default;
        explicit Frontier(T_Queue_Struct _nodes) : nodes(_nodes) {}
        virtual ~Frontier() = default;

        void insert(const node_type& node) {
            this->nodes.push(node);
        }

        bool is_empty() {
            return this->nodes.empty();
        }

        virtual node_type pop() = 0;
        virtual bool contain(const node_type &node) = 0;
        virtual node_type get_node(const node_type &node) = 0;
        virtual void substitute_node(const node_type &node_in_frontier, const node_type &new_node) = 0;
        virtual string frontier_to_string() = 0;
};