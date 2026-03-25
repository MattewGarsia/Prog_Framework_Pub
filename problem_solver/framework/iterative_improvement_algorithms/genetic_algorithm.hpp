#pragma once
#include "search_state_successor.hpp"
#include "../libraries/random.hpp"
#include "genetic_operator.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class Genetic_Algorithm : public SearchStateSuccessor<T_Cost, T_State> {
    public:
        using base_type    = SearchStateSuccessor<T_Cost, T_State>;
        using problem_type = typename base_type::problem_type;
        using state_type   = typename base_type::state_type;
        using node_type    = typename base_type::node_type;
    
        int timer;
        double prob_mut;
        GeneticOperator<state_type>* op;

        Genetic_Algorithm(GeneticOperator<state_type>* operators, int timer_in = 100, double prob_mut_in = 0.05, int k = 10)
                                                : SearchStateSuccessor<T_Cost, T_State>(k), timer(timer_in), prob_mut(prob_mut_in), op(operators) {}
    
        vector<state_type> get_best_k_successors() {
            sort(this->successors.begin(), this->successors.end(),
                [](const state_type& a, const state_type& b){
                    return a.heuristic < b.heuristic;
                });
            vector<state_type> best;
            int min_el = min(this->k, (int)this->successors.size());
            for (int i = 0; i < min_el; i++)
                best.push_back(this->successors[i]);
            return best;
        }
    
        state_type best_in(const vector<state_type>& population) {
            return *min_element(population.begin(), population.end(),
                [](const state_type& a, const state_type& b){
                    return a.heuristic < b.heuristic;
                });
        }
    
        state_type build_child(const vector<state_type>& population) {
            int index1 = random_int(0, (int)population.size()-1);
            int index2 = random_int(0, (int)population.size()-1);
            const state_type& gen1 = population[index1];
            const state_type& gen2 = population[index2];
    
            int xover = random_int(1, op->genome_size(gen1) - 1); 
            state_type child = op->crossover(gen1, gen2, xover); 
            if (random_double(0, 1) < prob_mut) child = op->mutate(child);                 
            return child;
        }
    
        string search_solution(const problem_type& problem) override {
            vector<state_type> population = problem.current_population;
            int t = 0;
            while (true) {                                          
                state_type best = best_in(population);
    
                if (op->is_solution(best) || t >= timer)          
                    return best.name;
    
                this->successors.clear();                         
    
                while ((int)this->successors.size() < this->k)      
                    this->successors.push_back(build_child(population));
    
                population = get_best_k_successors();           
                t++;
            }
        }
};
