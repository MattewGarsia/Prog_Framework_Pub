#pragma once

#include "../general/solver.hpp"
#include "problem_curr_pop.hpp"
using namespace std;

template <typename T_Cost, typename T_State, typename T_Solution>
class Local_Search : public Solver<T_Cost, T_State, T_Solution, Problem_popul<T_Cost, T_State>>{
    public:
        using problem_type = Problem_popul<T_Cost, T_State>;
        using state_type = T_State;
        using node_type = General_Node<T_Cost, state_type>;
        //using problem_type = typename Local_Search<T_Cost, state_type, state_type>::problem_type;

        /*
        virtual bool stopping_policy() = 0;
        virtual state_type evolving_pop_policy() = 0;
        virtual void found_improvement() = 0;
        virtual void no_improvement_found() = 0;
        virtual state_type reset_return_policy() = 0;

        T_State search_solution(const problem_type& generic_problem) override {
            auto problem = dynamic_cast<const problem_type*>(&generic_problem);
            if (!problem) {
                throw invalid_argument("Hill_Climbing richiede un Problem_popul compatibile");
            }
            node_type current_node(problem->initial_node->current_state);
            
            while (true) {
                while (stopping_policy()) {
                    state_type next_state = evolving_pop_policy();
                    if (next_state.heuristic < current_node.current_state.heuristic) {
                        current_node = node_type(next_state, nullptr, current_node.cost, current_node.depth + 1);
                        found_improvement();
                    }
                    else{
                        no_improvement_found();
                    }
                }
                reset_return_policy();
            }
        }
        */
};