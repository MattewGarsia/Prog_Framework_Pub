#pragma once
#include <queue>
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"
#include "search_state_explorer_generic_algorithm.hpp"
#include "../general/heuristic_state.hpp"
using namespace std;

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class bfs : public SearchStateExplorer_GenericAlgo<T_Cost, T_State, queue<Types::node_type<T_Cost, T_State>>> {
    public:
        bfs(){
            this->frontier = new FIFO<T_Cost, T_State>();
        }
};