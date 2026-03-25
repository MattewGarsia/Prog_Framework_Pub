#pragma once
#include "../general/problem.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class Problem_popul : public Problem<T_Cost, T_State>{
    public:
        using base_type = Problem<T_Cost, T_State>;
        using node_type = typename base_type::node_type;
        using state_type = T_State;
        vector<state_type> current_population;
        int k;

        Problem_popul() = default;

        Problem_popul(node_type* _initial_node, vector<node_type*> _objectives, int _k) : Problem<T_Cost, T_State>(_initial_node, _objectives), k(_k) {
            current_population.push_back(_initial_node->current_state);
            this->initial_node = _initial_node;
            this->objective_nodes = _objectives;
            k = _k;
        }

        virtual state_type get_random_state() const = 0;
        virtual state_type get_random_neighbor(const state_type& state) const = 0;
        virtual state_type get_best_neighbor(const state_type& state) const = 0;

};