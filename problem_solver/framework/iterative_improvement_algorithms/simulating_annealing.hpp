#pragma once
#include "search_state_successor.hpp"
#include "../libraries/random.hpp"
#include <cmath>
using namespace std;

#define ALPHA 0.99
#define T0 100.0

template <typename T_Cost, typename T_State>
class Simulating_Annealing : public SearchStateSuccessor<T_Cost, T_State>{
    public:
        using base_type = SearchStateSuccessor<T_Cost, T_State>;
        using state_type = typename base_type::state_type;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = typename base_type::problem_type;

        Simulating_Annealing(int _k = 1) : SearchStateSuccessor<T_Cost, T_State>(_k) {}

        double cooling_speed_at_t(int t, double T){
            return T* pow(ALPHA, t);
        }

        string search_solution(const problem_type& problem) override {
            double T = T0;
            node_type current_node(problem.initial_node->current_state, nullptr, nullptr);
            int t = 0;
            while(true){
                T = cooling_speed_at_t(t, T);
                vector<typename node_type::action_type*> actions = problem.get_actions(current_node.current_state);
                if (T == 0) {
                    return current_node.current_state.name;
                }
                int k = random_int(0, static_cast<int>(actions.size()) - 1);
                state_type neighbor = problem.get_result(current_node.current_state, *actions[k]);
                if (neighbor.heuristic < current_node.current_state.heuristic){
                    current_node = node_type(neighbor, actions[k], new node_type(current_node));
                }
                else {
                    double delta_E = fabs(static_cast<double>(neighbor.heuristic - current_node.current_state.heuristic));
                    if (random_double(0, 1) < exp(-delta_E / T)) {
                        current_node = node_type(neighbor, actions[k], new node_type(current_node));
                    }
                }
                t++;
                //cout<<"current state: "<<current_node.current_state.name<<", heuristic: "<<current_node.current_state.heuristic<<", T: "<<T<<endl;  
            }
        }
};