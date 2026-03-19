#pragma once
#include "search_state_successor.hpp"
using namespace std;

template <typename T_Cost>
class GeneticAlgorithm : public SearchStateSuccessor<T_Cost, string, string> {
    public:
        using problem_type = typename SearchStateSuccessor::problem_type;
        using state_type = typename SearchStateSuccessor::state_type;
        using node_type = typename SearchStateSuccessor::node_type;
        int timer;
        double prob_mut;
        GeneticAlgorithm(int timer, double prob_mut) : timer(timer), prob_mut(prob_mut) {}

        state_type pop_corr_contains_good_solutions(vector<state_type> pop_corr){
            state_type new_state = pop_corr[0];
            for (state_type state : pop_corr){
                if(this->compare_quality(state, new_state)){
                    new_state = state;
                }
            }
            return new_state;
        }

        state_type substr(state_type state, int start, int end){
            string substr = "";
            for (int i = start; i <= end; i++){
                substr += state[i];
            }
            return substr; // Placeholder, da implementare
        }
        
        state_type mutate(state_type child){
            int change_value = random(0,9);
            int pos = random(0, child.size() - 1);
            child[pos] = change_value + '0';
            return child;
        }

        state_type build_child(vector<state_type> pop_corr){
            state_type gen1 = pop_corr[random_int(0, pop_corr.size() - 1)];
            state_type gen2 = pop_corr[random_int(0, pop_corr.size() - 1)];
            int xover = random_int(1, S);
            state_type substr1 = substr(gen1, 0, xover - 1);
            state_type substr2 = substr(gen2, xover, gen2.size() - 1);
            state_type child = substr1 + substr2;
            if (random_double(0, 1) < prob_mut) {
                mutate(child);
            }
            return child;
        }

        state_type search_solution(problem_type problem){
            vector<state_type> pop_corr = problem.current_population;
            while (true) {
                state_type best_sol = pop_corr_contains_good_solutions(pop_corr);
                if (best_sol) {
                    return best_sol;
                }
                while(this->successors.size() < this->k){
                    state_type child = build_child(pop_corr);
                    this->successors.push_back(child);
                }
                pop_corr = this->get_best_k_successors();
            }
        }
};