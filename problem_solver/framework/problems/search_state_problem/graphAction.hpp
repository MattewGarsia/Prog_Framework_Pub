#ifndef GRAPHACTION_HPP
#define GRAPHACTION_HPP

#include "../../general/action.hpp"
#include <string>

class graphAction : public Action<double, Heuristic_State<double>> {
    public:
        using base_type = Action<double, Heuristic_State<double>>;
        using state_type = typename base_type::state_type;

        graphAction(const state_type& destination_state, double cost_in)
            : base_type(destination_state, cost_in) {}
};

#endif