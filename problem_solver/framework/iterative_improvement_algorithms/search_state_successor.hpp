#pragma once
#include <vector>
#include <string>
#include "../general/search_state.hpp"
#include "../general/problem.hpp"
#include "../libraries/type.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class SearchStateSuccessor : public SearchState<T_Cost, T_State, string> {
    public:
        using state_type = T_State;
        using node_type = Types::node_type<T_Cost, state_type>;
        using problem_type = typename SearchState<T_Cost, T_State, string>::problem_type;
        vector<state_type> successors;
        int k;
        SearchStateSuccessor(int _k) : SearchState<T_Cost, T_State, string>(){
            this->k = _k;
        }

        vector<state_type> get_best_k_successors() {
            sort(this->successors.begin(), this->successors.end(),
                [](const state_type& a, const state_type& b) {
                    return a.heuristic < b.heuristic;
                });
            vector<state_type> best;
            for (int i = 0; i < min(this->k, (int)this->successors.size()); i++)
                best.push_back(this->successors[i]);
            return best;
        }
};