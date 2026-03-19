#pragma once
#include <vector>
#include <string>
#include "../general/search_state.hpp"
using namespace std;

template <typename T_Cost, typename T_State>
class SearchStateSuccessor : public SearchState<T_Cost, T_State, string> {
    public:
        using state_type = T_State;
        vector<state_type> successors;
        int k;
        SearchStateSuccessor(int _k) : SearchState(){
            this->k = _k;
        }

        vector<state_type> get_best_k_successors(){
            vector<state_type> best_successors;
            for (int i = 0; i < min(k, (int)successors.size()); i++){
                best_successors.push_back(successors[i]);
            }
            return best_successors;
        }
};