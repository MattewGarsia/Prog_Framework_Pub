#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "../general/state.hpp"
#include "../general/node.hpp"
#include "../general/frontier.hpp"
#include "../libraries/type.hpp"
#include "../general/search_state.hpp"
#include "../general/problem.hpp"
#include "problem_state_explorer.hpp"
using namespace std;

template <typename T_Cost,typename T_State, typename T_Queue_Struct>
class SearchStateExplorer : public SearchState<T_Cost, T_State, vector<Node<T_Cost, T_State>>> {
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, T_State>;
        using problem_type = Types::problem_type<T_Cost, T_State>;
        using explorer_problem_type = ProblemStateExplorer<T_Cost, T_State>;
        using frontier_type = Types::frontier_type<T_Cost, T_State, T_Queue_Struct>;

        frontier_type* frontier = nullptr;
        vector<state_type> explored;

        virtual vector<node_type> search_solution(const problem_type &problem) = 0;

        bool contain(const vector<state_type>& explored_states, const state_type& state) {
            for (const state_type& s : explored_states) {
                if (s.name == state.name){
                    return true;
                }
            }
            return false;
        }

        vector<node_type> build_solution(node_type node) {
            vector<node_type> path;
            while (true){
                path.push_back(node);
                if (node.parent_node == nullptr){
                    break;
                }
                node = *node.parent_node;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        string vector_to_string(const vector<state_type>& vec) {
            string result = "";
            for (const state_type& state : vec){
                result += state.name + " ";
            }
            return result;
        }


        void print_iteration(node_type node, int iter, bool is_child = false){
            #define PRINT_ON 0


            //elimino i warning 
            #if !PRINT_ON
            (void)node;
            (void)iter;
            (void)is_child;
            #endif

            #if PRINT_ON
            string result = "";
            if (is_child){
                result += "child: " + node.current_state.name + ", cost: " + to_string(node.cost);
            } else {
                result += "node: " + node.current_state.name + ", cost: " + to_string(node.cost);
            }
            result += "| frontier: "+ this->frontier->frontier_to_string();
            result += "| explored: "+ this->vector_to_string(explored);
            result += "| iteration: " + to_string(iter);

            result+="\n";
            cout<<result;
            #endif
        }
};

template <typename T_Cost, typename T_State, typename T_Queue_Struct>
class SearchStateExplorer_GenericAlgo : public SearchStateExplorer<T_Cost, T_State, T_Queue_Struct> {
    public:
        using base_type = SearchStateExplorer<T_Cost, T_State, T_Queue_Struct>;
        using typename base_type::node_type;
        using typename base_type::problem_type;
        using typename base_type::state_type;

        vector<node_type> search_solution(const problem_type &problem) override {
            //controllo se è un StateExplorerProblem
            auto explorer_problem = dynamic_cast<const typename base_type::explorer_problem_type*>(&problem);
            if (!explorer_problem) {
                cout<<"Error: problem is not of type ProblemStateExplorer."<<endl;
                return {};
            }

            node_type initial_node(problem.initial_node->current_state, nullptr, nullptr);
            this->frontier->insert(initial_node);
            
            while (!this->frontier->is_empty()){
                node_type node = this->frontier->pop();
                this->explored.push_back(node.current_state);
                this->print_iteration(node, this->iter, false);
                if (node.current_state.is_objective()){
                    return this->build_solution(node);
                }
                vector<typename node_type::action_type*> actions = explorer_problem->get_actions(node.current_state);
                for (auto action : actions){
                    state_type child_state = problem.get_result(*action);
                    if (!this->contain(this->explored, child_state)){
                        node_type child_node(child_state, action, new node_type(node));
                        if(!this->frontier->contain(child_node)){
                            this->frontier->insert(child_node);
                        }
                        else{
                            node_type frontier_child = this->frontier->get_node(child_node);
                            if (child_node.cost < frontier_child.cost){
                                this->frontier->substitute_node(frontier_child, child_node);
                            }
                        }
                        this->print_iteration(child_node, this->iter, true);
                    }
                }
                this->iter++;
            }
            return {};
        }
};