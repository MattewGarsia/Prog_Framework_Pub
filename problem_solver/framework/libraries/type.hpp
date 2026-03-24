#pragma once
#include <queue>
#include "../general/node.hpp"
#include "../general/state.hpp"
#include "../general/frontier.hpp"

template <typename T_Cost, typename T_State>
class Problem;

namespace Types {
    using state_value_t = int;
    using cost_value_t = int;

    template <typename T_Cost = cost_value_t>
    using state_type = State<T_Cost>;

    template <typename T_Cost = cost_value_t, typename T_State = state_type<T_Cost>>
    using node_type = Node<T_Cost, T_State>;

    template <typename T_Cost = cost_value_t, typename T_State = state_type<T_Cost>>
    using problem_type = Problem<T_Cost, T_State>;

    template <
        typename T_Cost = cost_value_t,
        typename T_State = state_type<T_Cost>,
        typename T_Queue_Struct = std::queue<node_type<T_Cost, T_State>>>
    using frontier_type = Frontier<T_Cost, T_State, T_Queue_Struct>;
}

namespace State_Type {
    template <typename T_Cost = Types::cost_value_t>
    using state_type = Types::state_type<T_Cost>;
}

namespace Node_Type {
    template <typename T_Cost = Types::cost_value_t>
    using state_type = Types::state_type<T_Cost>;

    template <typename T_Cost = Types::cost_value_t, typename T_State = Types::state_type<T_Cost>>
    using node_type = Types::node_type<T_Cost, T_State>;
}

namespace Algorithms {
    template <
        typename T_Cost = Types::cost_value_t,
        typename T_State = Types::state_type<T_Cost>,
        typename T_Queue_Struct = std::queue<Types::node_type<T_Cost, T_State>>>
    using problem_type = Types::problem_type<T_Cost, T_State>;

    template <typename T_Cost = Types::cost_value_t>
    using state_type = Types::state_type<T_Cost>;

    template <typename T_Cost = Types::cost_value_t, typename T_State = Types::state_type<T_Cost>>
    using node_type = Types::node_type<T_Cost, T_State>;
}

namespace Frontier_Type {
    template <typename T_Cost = Types::cost_value_t, typename T_State = Types::state_type<T_Cost>>
    using node_type = Types::node_type<T_Cost, T_State>;

    template <
        typename T_Cost = Types::cost_value_t,
        typename T_State = Types::state_type<T_Cost>,
        typename T_Queue_Struct = std::queue<Types::node_type<T_Cost, T_State>>>
    using frontier_type = Types::frontier_type<T_Cost, T_State, T_Queue_Struct>;

    template <typename T_Cost = Types::cost_value_t>
    using state_type = Types::state_type<T_Cost>;

    template <typename T_Cost = Types::cost_value_t, typename T_State = Types::state_type<T_Cost>>
    using problem_type = Types::problem_type<T_Cost, T_State>;
}