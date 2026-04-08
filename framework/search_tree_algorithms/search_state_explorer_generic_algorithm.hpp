#pragma once
#include "search_state_explorer.hpp"

using namespace std;

template <typename T_Cost, typename T_State, typename T_Queue_Struct>
class SearchStateExplorer_GenericAlgo : public SearchStateExplorer<T_Cost, T_State, T_Queue_Struct> {
    public:
        using base_type = SearchStateExplorer<T_Cost, T_State, T_Queue_Struct>;
        using typename base_type::node_type;
        using typename base_type::problem_type;
        using typename base_type::state_type;

        virtual void insert_policy(const problem_type &problem, const node_type &node, 
                                  const typename node_type::action_type *action, const state_type &child_state) {
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
                this->print_iteration(child_node, this->get_iter(), true);
            }
        }

        vector<node_type> search_solution(const problem_type &problem) override {
            //controllo se è un StateExplorerProblem
            auto explorer_problem = dynamic_cast<const typename base_type::problem_type*>(&problem);
            if (!explorer_problem) {
                cout<<"Error: problem is not of type ProblemStateExplorer."<<endl;
                return {};
            }

            node_type initial_node(problem.initial_node->current_state, nullptr, nullptr);
            this->frontier->insert(initial_node);
            
            while (!this->frontier->is_empty()){
                node_type node = this->frontier->pop();
                this->explored.push_back(node.current_state);
                this->print_iteration(node, this->get_iter(), false);
                if (node.current_state.is_objective()){
                    return this->build_solution(node);
                }
                vector<typename node_type::action_type*> actions = explorer_problem->get_actions(node.current_state);
                for (auto action : actions){
                    state_type child_state = problem.get_result(*action);
                    insert_policy(problem, node, action, child_state);
                }
                this->set_iter(this->get_iter() + 1);
            }
            return {};
        }
};