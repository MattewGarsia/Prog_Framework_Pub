#pragma once
#include "search_state_successor.hpp"
#include "../libraries/random.hpp"
#include "../iterative_improvement_algorithms/problem_curr_pop.hpp"
#include <cmath>
using namespace std;

#define ALPHA 0.99
#define T0 100.0
#define T_MIN 0.01

template <typename T_Cost, typename T_State>
class Simulating_Annealing : public SearchStateSuccessor<T_Cost, T_State>{
    public:
        using base_type = SearchStateSuccessor<T_Cost, T_State>;
        using state_type = typename base_type::state_type;
        using node_type = General_Node<T_Cost, state_type>;
        using problem_type = Problem_popul<T_Cost, state_type>;

        Simulating_Annealing(int _k = 1) : SearchStateSuccessor<T_Cost, T_State>(_k) {}

        double cooling_speed_at_t(double T){
            if (T < T_MIN) return 0.0;
            return T*ALPHA;
        }

        string search_solution(const typename base_type::problem_type& generic_problem) override {
            auto problem = dynamic_cast<const problem_type*>(&generic_problem);
            if (!problem) {
                throw invalid_argument("Simulating_Annealing richiede un Problem_popul compatibile");
            }

            double T = T0;
            node_type current_node(problem->initial_node->current_state);
            int t = 0;
            while(true){
                T = cooling_speed_at_t(T);
                if (T == 0.0) {
                    T = T0;
                    current_node = node_type(problem->initial_node->current_state);
                }
                state_type neighbor = problem->get_random_neighbor(current_node.current_state);
                if (neighbor.heuristic < current_node.current_state.heuristic){
                    current_node = node_type(neighbor, nullptr, current_node.cost, current_node.depth + 1);
                }
                else {
                    double delta_E = fabs(static_cast<double>(neighbor.heuristic - current_node.current_state.heuristic));
                    if (random_double(0, 1) < exp(-delta_E / T)) {
                        current_node = node_type(neighbor, nullptr, current_node.cost, current_node.depth + 1);
                    }
                }

                if (current_node.current_state.heuristic == 0) {
                    //cout<<"Soluzione trovata in "<<t<<" iterazioni, T: "<<T<<endl;
                    return current_node.current_state.name;
                }

                t++;
                //cout<<"t: "<<t<<", T: "<<T<<endl;
                //cout<<"current state: "<<current_node.current_state.name<<", heuristic: "<<current_node.current_state.heuristic<<", T: "<<T<<endl;  
            }
        }
};