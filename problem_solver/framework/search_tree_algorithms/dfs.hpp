#pragma once
#include <stack>
#include "search_state_explorer.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class dfs : public SearchStateExplorer_GenericAlgo<T_Cost, T_State, stack<Types::node_type<T_Cost, T_State>>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Cost, T_State,stack<Types::node_type<T_Cost, T_State>>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        dfs(){
            this->frontier = new LIFO<T_Cost, T_State>();
        }

        vector<node_type> search_solution(const problem_type &problem) override {
            auto explorer_problem = dynamic_cast<const typename base_type::explorer_problem_type*>(&problem);
            if (!explorer_problem) {
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