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

template<typename T_Cost, typename T_State, typename T_Queue_Struct>
class Frontier_Generic_Queuing_Structure : public Frontier<T_Cost, T_State, T_Queue_Struct> {
    public:
        using node_type = Node<T_Cost, T_State>;

        node_type pop() override {
            node_type node = this->nodes.top();
            this->nodes.pop();
            return node;
        }

        void substitute_node(const node_type &old_node, const node_type &new_node) override {
            vector<node_type> node_list;
            while (!this->nodes.empty()) {
                node_type current = this->nodes.top();
                this->nodes.pop();
                if (current.current_state.name == old_node.current_state.name) {
                    node_list.push_back(new_node);
                } else {
                    node_list.push_back(current);
                }
            }
            for (const node_type& node : node_list) {
                this->nodes.push(node);
            }
        }
};

template<typename T_Cost, typename T_State, typename T_Queue_Struct>
class Frontier_Priority_Queue : public Frontier_Generic_Queuing_Structure<T_Cost, T_State, T_Queue_Struct> {
    public:
        using node_type = Node<T_Cost, T_State>;
        using pq_type = T_Queue_Struct;
        bool contain(const node_type &node) override {
                pq_type priority_queue_temp = this->nodes;
                while (!priority_queue_temp.empty()) {
                    if (priority_queue_temp.top().current_state.name == node.current_state.name)
                        return true;
                    priority_queue_temp.pop();
                }
                return false;
            }

        node_type get_node(const node_type &node) override {
            pq_type priority_queue_temp = this->nodes;
            while (!priority_queue_temp.empty()) {
                if (priority_queue_temp.top().current_state.name == node.current_state.name)
                    return priority_queue_temp.top();
                priority_queue_temp.pop();
            }
            throw runtime_error("Node not found in frontier");
        }
    

        string frontier_to_string() override {
            pq_type priority_queue_temp = this->nodes;
            string result = "[";
            while (!priority_queue_temp.empty()) {
                result += priority_queue_temp.top().current_state.name + "(g: " + std::to_string(priority_queue_temp.top().cost) + ")";
                priority_queue_temp.pop();
                if (!priority_queue_temp.empty()) {
                    result += ", ";
                }
            }
            result += "]";
            return result;
        }
};