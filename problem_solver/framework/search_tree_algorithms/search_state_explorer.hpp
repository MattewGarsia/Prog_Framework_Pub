#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "problem_state_explorer.hpp"
#include "../general/state.hpp"
#include "../general/node.hpp"
#include "../general/frontier.hpp"
#include "../general/search_state.hpp"
#include "../general/problem.hpp"
#include "../libraries/type.hpp"
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