#pragma once

#include <queue>
#include <stack>
#include <vector>
#include "frontier.hpp"
#include "compare_cost.hpp"
using namespace std;

//  FIFO (BFS)
template <typename T_Type_State_Value, typename T_Type_State>
class FIFO : public Frontier<T_Type_State_Value, T_Type_State,
                    queue<Node<T_Type_State_Value, T_Type_State>>> {
    public:
        using base_type = Frontier<T_Type_State_Value, T_Type_State,
                        queue<Node<T_Type_State_Value, T_Type_State>>>;
        using node_type = Node<T_Type_State_Value, T_Type_State>;

        FIFO() { this->nodes = queue<node_type>(); }

        node_type pop() override {
            node_type n = this->nodes.front();
            this->nodes.pop();              
            return n;
        }

        bool contain(const node_type &node) override {
            queue<node_type> tmp = this->nodes;
            while (!tmp.empty()) {
                if (tmp.front().current_state.name == node.current_state.name)
                    return true;
                tmp.pop();
            }
            return false;
        }

        node_type get_node(const node_type &node) override {
            queue<node_type> tmp = this->nodes;
            while (!tmp.empty()) {
                if (tmp.front().current_state.name == node.current_state.name)
                    return tmp.front();
                tmp.pop();
            }
            throw runtime_error("Node not found in frontier");
        }

        void substitute_node(const node_type &old_node, const node_type &new_node) override {
            queue<node_type> tmp;
            while (!this->nodes.empty()) {
                node_type n = this->nodes.front();
                this->nodes.pop();
                if (n.current_state.name == old_node.current_state.name)
                    tmp.push(new_node);
                else
                    tmp.push(n);
            }
            this->nodes = tmp;
        }

        string frontier_to_string() override {
            queue<node_type> tmp = this->nodes;
            string result = "FIFO: [";
            while (!tmp.empty()) {
                result += tmp.front().current_state.name + "(c: " + std::to_string(tmp.front().cost) + ")";
                tmp.pop();
                if (!tmp.empty()) result += ", ";
            }
            result += "]";
            return result;
        }
};

template <typename T_Type_State_Value, typename T_Type_State>
class LIFO : public Frontier_Generic_Queuing_Structure<T_Type_State_Value, T_Type_State,
                    stack<Node<T_Type_State_Value, T_Type_State>>> {
    public:
        using base_type = Frontier_Generic_Queuing_Structure<T_Type_State_Value, T_Type_State,
                        stack<Node<T_Type_State_Value, T_Type_State>>>;
        using node_type = Node<T_Type_State_Value, T_Type_State>;

        LIFO() { this->nodes = stack<node_type>(); }

        bool contain(const node_type& node) override {
            stack<node_type> tmp = this->nodes;
            while (!tmp.empty()) {
                if (tmp.top().current_state.name == node.current_state.name) {
                    return true;
                }
                tmp.pop();
            }
            return false;
        }

        node_type get_node(const node_type& node) override {
            stack<node_type> tmp = this->nodes;
            while (!tmp.empty()) {
                if (tmp.top().current_state.name == node.current_state.name) {
                    return tmp.top();
                }
                tmp.pop();
            }
            throw runtime_error("Node not found in frontier");
        }

        string frontier_to_string() override {
            stack<node_type> tmp = this->nodes;
            string result = "LIFO: [";
            while (!tmp.empty()) {
                result += tmp.top().current_state.name + "(c: " + std::to_string(tmp.top().cost) + ")";
                tmp.pop();
                if (!tmp.empty()) result += ", ";
            }
            result += "]";
            return result;
        }
};

//  Min_G_Cost (costo cammino)
template <typename T_Type_State_Value, typename T_Type_State>
class Min_G_Cost : public Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                    priority_queue<Node<T_Type_State_Value, T_Type_State>,
                    vector<Node<T_Type_State_Value, T_Type_State>>,
                    Compare_G_Cost>> {
    public:
        using base_type = Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                        priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_G_Cost>>;
        using queue_type = priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_G_Cost>;

        Min_G_Cost() { this->nodes = queue_type(); }
};

//  Min_Objective_Cost (euristica h(n))
template <typename T_Type_State_Value, typename T_Type_State>
class Min_H_Cost : public Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                    priority_queue<Node<T_Type_State_Value, T_Type_State>, 
                    vector<Node<T_Type_State_Value, T_Type_State>>, 
                    Compare_H_Cost>> {
    public:
        using base_type = Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                        priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_H_Cost>>;
        using queue_type = priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_H_Cost>;

        Min_H_Cost() { this->nodes = queue_type(); }
};

//  Min_F_Cost (A* -> f(n) = g(n) + h(n))
template <typename T_Type_State_Value, typename T_Type_State>
class Min_F_Cost : public Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                priority_queue<Node<T_Type_State_Value, T_Type_State>, 
                vector<Node<T_Type_State_Value, T_Type_State>>, 
                Compare_F_Cost>> {
    public:
        using base_type = Frontier_Priority_Queue<T_Type_State_Value, T_Type_State,
                        priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_F_Cost>>;
        using queue_type = priority_queue<Node<T_Type_State_Value, T_Type_State>,
                        vector<Node<T_Type_State_Value, T_Type_State>>,
                        Compare_F_Cost>;

        Min_F_Cost() { this->nodes = queue_type(); }
};