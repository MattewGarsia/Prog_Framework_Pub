#pragma once
#include "search_state_successor.hpp"
using namespace std;

template <typename T_Cost>
class SimulatingAnnealing : public SearchStateSuccessor<T_Cost>{
    public:
        using state_type = typename SearchStateSuccessor<T_Cost>::state_type;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = Types::problem_type<T_Cost, state_type>;

        double cooling_speed_at_t(double cooling_speed, int t){
            return cooling_speed;
        }

        state_type search_solution(problem_type& problem, double cooling_speed) override{
            node_type current_node(problem.initial_node.current_state, nullptr, 0);
            int t = 0;
            while(true){
                double T = cooling_speed_at_t(cooling_speed, t);
                if (T == 0) return current_node;
                int k = random_range(0, problem.get_actions(current_node.current_state).size() - 1);
                state_type neighbor = problem.get_actions(current_node.current_state)[k];
                if (this->compare_quality(neighbor, current_node)){
                    current_node = neighbor;
                }
                else {
                    double delta_E = abs(this->get_quality(neighbor) - this->get_quality(current_node));
                    if (random_double(0, 1) < exp(-delta_E / T)){
                        current_node = neighbor;
                    }
                }
                t++;
            }
        }
};