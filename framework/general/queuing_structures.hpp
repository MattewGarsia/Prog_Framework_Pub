#pragma once

#include <queue>
#include <stack>
#include <vector>
#include "frontier.hpp"
#include "frontier_generic_queuing_structure.hpp"
#include "compare.hpp"
using namespace std;

//  FIFO (BFS)
template <typename T_Cost, typename T_State>
class FIFO : public Frontier<T_Cost, T_State, queue<Node<T_Cost, T_State>>> {
    public:
        using base_type = Frontier<T_Cost, T_State, queue<Node<T_Cost, T_State>>>;
        using node_type = Node<T_Cost, T_State>;

        FIFO() { this->nodes = queue<node_type>(); }

        node_type pop() override {
            node_type n = this->nodes.front();
            this->nodes.pop();              
            return n;
        }

        bool contain(const node_type &node) override {
            queue<node_type> temp_queue = this->nodes;
            while (!temp_queue.empty()) {
                if (temp_queue.front().current_state.name == node.current_state.name)
                    return true;
                temp_queue.pop();
            }
            return false;
        }

        node_type get_node(const node_type &node) override {
            queue<node_type> temp_queue = this->nodes;
            while (!temp_queue.empty()) {
                if (temp_queue.front().current_state.name == node.current_state.name)
                    return temp_queue.front();
                temp_queue.pop();
            }
            throw runtime_error("Node not found in frontier");
        }

        void substitute_node(const node_type &old_node, const node_type &new_node) override {
            queue<node_type> temp_queue = this->nodes;
            while (!this->nodes.empty()) {
                node_type n = this->nodes.front();
                this->nodes.pop();
                if (n.current_state.name == old_node.current_state.name)
                    temp_queue.push(new_node);
                else
                    temp_queue.push(n);
            }
            this->nodes = temp_queue;
        }

        string frontier_to_string() override {
            queue<node_type> temp_queue = this->nodes;
            string result = "FIFO: [";
            while (!temp_queue.empty()) {
                result += temp_queue.front().current_state.name + "(c: " + std::to_string(temp_queue.front().cost) + ")";
                temp_queue.pop();
                if (!temp_queue.empty()) result += ", ";
            }
            result += "]";
            return result;
        }
};

template <typename T_Cost, typename T_State>
class LIFO : public Frontier_Generic_Queuing_Structure<T_Cost, T_State, stack<Node<T_Cost, T_State>>> {
    public:
        using base_type = Frontier_Generic_Queuing_Structure<T_Cost, T_State, stack<Node<T_Cost, T_State>>>;
        using node_type = Node<T_Cost, T_State>;

        LIFO() { this->nodes = stack<node_type>(); }
        /*
        bool contain(const node_type& node) override {
            stack<node_type> temp_stack = this->nodes;
            while (!temp_stack.empty()) {
                if (temp_stack.top().current_state.name == node.current_state.name) {
                    return true;
                }
                temp_stack.pop();
            }
            return false;
        }

        node_type get_node(const node_type& node) override {
            stack<node_type> temp_stack = this->nodes;
            while (!temp_stack.empty()) {
                if (temp_stack.top().current_state.name == node.current_state.name) {
                    return temp_stack.top();
                }
                temp_stack.pop();
            }
            throw runtime_error("Node not found in frontier");
        }

        string frontier_to_string() override {
            stack<node_type> temp_stack = this->nodes;
            string result = "LIFO: [";
            while (!temp_stack.empty()) {
                result += temp_stack.top().current_state.name + "(c: " + std::to_string(temp_stack.top().cost) + ")";
                temp_stack.pop();
                if (!temp_stack.empty()) result += ", ";
            }
            result += "]";
            return result;
        }
        */
};

//  Min_G_Cost (costo cammino)
template <typename T_Cost, typename T_State>
class Min_G_Cost : public Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                    priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                    Compare_G_Cost>> {
    public:
        using base_type = Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                        priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                        Compare_G_Cost>>;
        using queue_type = priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                        Compare_G_Cost>;

        Min_G_Cost() { this->nodes = queue_type(); }
};

//  Min_Objective_Cost (euristica h(n))
template <typename T_Cost, typename T_State>
class Min_H_Cost : public Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                    priority_queue<Node<T_Cost, T_State>, vector<Node<T_Cost, T_State>>, 
                    Compare_H_Cost>> {
    public:
        using base_type = Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                        priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                        Compare_H_Cost>>;
        using queue_type = priority_queue<Node<T_Cost, T_State>, vector<Node<T_Cost, T_State>>,
                        Compare_H_Cost>;

        Min_H_Cost() { this->nodes = queue_type(); }
};

//  Min_F_Cost (f(n) = g(n) + h(n))
template <typename T_Cost, typename T_State>
class Min_F_Cost : public Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                priority_queue<Node<T_Cost, T_State>, vector<Node<T_Cost, T_State>>, 
                Compare_F_Cost>> {
    public:
        using base_type = Frontier_Generic_Queuing_Structure<T_Cost, T_State,
                        priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                        Compare_F_Cost>>;
        using queue_type = priority_queue<Node<T_Cost, T_State>,vector<Node<T_Cost, T_State>>,
                        Compare_F_Cost>;

        Min_F_Cost() { this->nodes = queue_type(); }
};