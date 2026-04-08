#pragma once

#include <stack>
#include "search_state_explorer_generic_algorithm.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"
#include "../general/heuristic_state.hpp"
using namespace std;

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class a_star : public SearchStateExplorer_GenericAlgo<T_Cost, T_State,
                            priority_queue<Types::node_type<T_Cost, T_State>, vector<Types::node_type<T_Cost, T_State>>,
                            Compare_F_Cost>> {
    public:
        a_star(){
            this->frontier = new Min_F_Cost<T_Cost, T_State>();
        }
};