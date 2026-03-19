#pragma once
#include "search_state_successor.hpp"
using namespace std;

template <typename T_Cost>
class LocalBeam : public SearchStateSuccessor<T_Cost>{
    public:
        using state_type = typename SearchStateSuccessor<T_Cost>::state_type;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = Types::problem_type<T_Cost, state_type>;
        LocalBeam() : SearchStateSuccessor<T_Cost, state_type, state_type>(){  

        }

        state_type search_solution(problem_type& problem) override{
            vector<state_type> current_pop = problem.current_population;
            while (true)
            {
                for (State state : current_pop){
                    for (Action action : problem.get_actions(state)){
                        state_type neighbor = problem.get_result(state, action);
                        this->successor.push_back(neighbor);
                        if (neighbor.is_objective()){
                            return this->solution(neighbor);
                        }
                    }
                    current_pop = this->get_best_k_successors();
                }
            }
        }
};