#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "node.hpp"

using namespace std;

template<typename T_Type_Cost, typename T_Type_State,  typename T_Queue_Struct>
class Frontier {
    public:
        using node_type = Node<T_Type_Cost, T_Type_State>;

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

template<typename T_Type_Cost, typename T_Type_State, typename T_Queue_Struct>
class Frontier_Generic_Queuing_Structure : public Frontier<T_Type_Cost, T_Type_State, T_Queue_Struct> {
    public:
        using node_type = Node<T_Type_Cost, T_Type_State>;

        node_type pop() override {
            node_type node = this->nodes.top();
            this->nodes.pop();
            return node;
        }

        void substitute_node(const node_type &old_node, const node_type &new_node) override {
            vector<node_type> tmp;
            while (!this->nodes.empty()) {
                node_type current = this->nodes.top();
                this->nodes.pop();
                if (current.current_state.name == old_node.current_state.name) {
                    tmp.push_back(new_node);
                } else {
                    tmp.push_back(current);
                }
            }
            for (const node_type& node : tmp) {
                this->nodes.push(node);
            }
        }
};

template<typename T_Type_Cost, typename T_Type_State, typename T_Queue_Struct>
class Frontier_Priority_Queue : public Frontier_Generic_Queuing_Structure<T_Type_Cost, T_Type_State, T_Queue_Struct> {
    public:
        using node_type = Node<T_Type_Cost, T_Type_State>;
        using pq_type = T_Queue_Struct;
        bool contain(const node_type &node) override {
                pq_type tmp = this->nodes;
                while (!tmp.empty()) {
                    if (tmp.top().current_state.name == node.current_state.name)
                        return true;
                    tmp.pop();
                }
                return false;
            }

        node_type get_node(const node_type &node) override {
            pq_type tmp = this->nodes;
            while (!tmp.empty()) {
                if (tmp.top().current_state.name == node.current_state.name)
                    return tmp.top();
                tmp.pop();
            }
            throw runtime_error("Node not found in frontier");
        }
    

        string frontier_to_string() override {
            pq_type tmp = this->nodes;
            string result = "Min_G_Cost: [";
            while (!tmp.empty()) {
                result += tmp.top().current_state.name + "(g: " + std::to_string(tmp.top().cost) + ")";
                tmp.pop();
                if (!tmp.empty()) {
                    result += ", ";
                }
            }
            result += "]";
            return result;
        }
};