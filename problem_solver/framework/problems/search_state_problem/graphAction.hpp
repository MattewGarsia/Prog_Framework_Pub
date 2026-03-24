#pragma once

#include "../../general/action.hpp"
#include <string>

class graphAction : public Action<double, Heuristic_State<double>> {
    public:
        using base_type = Action<double, Heuristic_State<double>>;
        using state_type = typename base_type::state_type;

        graphAction(const state_type& dest_state, double cost_) : base_type(dest_state, cost_) {}
};