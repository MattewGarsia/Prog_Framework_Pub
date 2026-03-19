#pragma once

#include <queue>
#include <stack>
#include "general/problem_solver.hpp"
#include "queuing_structures.hpp"
#include "type.hpp"

template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class dfs : public SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                stack<Types::node_type<T_Type_State_Value, T_Type_State>>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        stack<Types::node_type<T_Type_State_Value, T_Type_State>>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        dfs(){
            this->frontier = new LIFO<T_Type_State_Value, T_Type_State>();
        }

        vector<node_type> search_solution(const problem_type &problem) override {
            
            node_type initial_node(problem.initial_node->current_state, nullptr, nullptr);
            this->frontier->insert(initial_node);
            
            while (!this->frontier->is_empty()){
                node_type node = this->frontier->pop();
                this->explored.push_back(node.current_state);
                this->print_iteration(node, this->iter, false);
                if (node.current_state.is_objective()){
                    return this->solution(node);
                }
                vector<typename node_type::action_type*> actions = problem.get_actions(node.current_state);
                for (auto action : actions){
                    state_type child_state = problem.get_result(node.current_state, *action);
                    if (!this->contain(this->explored, child_state) && !this->frontier->contain(node_type(child_state, nullptr, nullptr))){
                        node_type child_node(child_state, action, new node_type(node));
                        this->frontier->insert(child_node);
                        this->print_iteration(child_node, this->iter, true);
                    }
                }
                this->iter++;
            }
            return {};
        }
};

template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class bfs : public SearchStateExplorer<T_Type_State_Value, T_Type_State,
            queue<Types::node_type<T_Type_State_Value, T_Type_State>>> {
    public:
        using base_type = SearchStateExplorer<T_Type_State_Value, T_Type_State,
                        queue<Types::node_type<T_Type_State_Value, T_Type_State>>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        bfs(){
            this->frontier = new FIFO<T_Type_State_Value, T_Type_State>();
        }

        vector<node_type> search_solution(const problem_type &problem) override {
            node_type initial_node(problem.initial_node->current_state, nullptr, nullptr);
            this->frontier->insert(initial_node);
            
            while (!this->frontier->is_empty()){
                node_type node = this->frontier->pop();
                this->explored.push_back(node.current_state);
                this->print_iteration(node, this->iter, false);
                vector<typename node_type::action_type*> actions = problem.get_actions(node.current_state);
                for (auto action : actions){
                    typename base_type::state_type child_state = problem.get_result(node.current_state, *action);
                     
                    if (!this->contain(this->explored, child_state) && !this->frontier->contain(node_type(child_state, nullptr, nullptr))){
                        node_type child_node(child_state, action, new node_type(node));
                        if (child_state.is_objective()){
                            return this->solution(child_node);
                        }
                        this->frontier->insert(child_node);
                        this->print_iteration(child_node, this->iter, true);
                    }
                }
                this->iter++;
            }
            return {};
        }
};

template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class min_cost : public SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                Compare_G_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                        vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                        Compare_G_Cost>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        min_cost(){
            this->frontier = new Min_G_Cost<T_Type_State_Value, T_Type_State>();
        }

};

template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class best_first_greedy : public SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                        vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                        Compare_H_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                        vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                        Compare_H_Cost>>;
        using typename base_type::problem_type;

        best_first_greedy(){
            this->frontier = new Min_H_Cost<T_Type_State_Value, T_Type_State>();
        }
};


template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class a_star : public SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                            priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                            vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                            Compare_F_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                        vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                        Compare_F_Cost>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        a_star(){
            this->frontier = new Min_F_Cost<T_Type_State_Value, T_Type_State>();
        }
};