#pragma once

#include <vector>
#include "../general/heuristic_state.hpp"
using namespace std;

template<typename T_Domain>
class Variable : public HeuristicState {
    public:
        vector<T_Domain> domain;

        vector<T_Domain> get_domain(){
            return domain;
        }
};