
#pragma once

#include <vector>
#include "action.hpp"
#include "../libraries/type.hpp"

using namespace std;

template <typename T_Cost, typename T_State>
class Problem {
    public:
        using node_type = Types::node_type<T_Cost, T_State>;
        using state_type = T_State;
        using action_type = Action<T_Cost, T_State>;

        node_type* initial_node = nullptr;
        vector<node_type*> objective_nodes;

        Problem() = default;
        
        Problem(node_type* _initial_node, vector<node_type*> _objectives)
        {
            initial_node = _initial_node;
            objective_nodes = _objectives;
        }
        
        virtual state_type get_result(const action_type& action) const = 0;
};