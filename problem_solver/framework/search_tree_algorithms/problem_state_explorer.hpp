#pragma once

#include "../general/problem.hpp"

template <typename T_Cost, typename T_State>
class ProblemStateExplorer : public Problem<T_Cost, T_State> {
    public:
        using base_type = Problem<T_Cost, T_State>;
        using node_type = typename base_type::node_type;
        using state_type = T_State;
        using action_type = Action<T_Cost, T_State>;

        ProblemStateExplorer(node_type* _initial_node, vector<node_type*> _objectives) {
            this->initial_node = _initial_node;
            this->objective_nodes = _objectives;
        }

        virtual vector<action_type*> get_actions(const state_type& state) const = 0;

};