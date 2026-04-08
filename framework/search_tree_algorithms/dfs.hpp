#pragma once
#include <stack>
#include "search_state_explorer_generic_algorithm.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class dfs : public SearchStateExplorer_GenericAlgo<T_Cost, T_State, stack<Types::node_type<T_Cost, T_State>>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Cost, T_State,stack<Types::node_type<T_Cost, T_State>>>;
        using problem_type = typename base_type::problem_type;
        using state_type = typename base_type::state_type;
        using node_type = typename base_type::node_type;
        using action_type = typename node_type::action_type;

        dfs(){
            this->frontier = new LIFO<T_Cost, T_State>();
        }

        void insert_policy(const problem_type &problem, const node_type &node, 
                           const action_type *action, const state_type &child_state) {
            if (!this->contain(this->explored, child_state) && !this->frontier->contain(node_type(child_state, nullptr, nullptr))){
                node_type child_node(child_state, action, new node_type(node));
                this->frontier->insert(child_node);
                this->print_iteration(child_node, this->get_iter(), true);
            }
        }
};