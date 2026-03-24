#pragma once
#include <stack>
#include "search_state_explorer.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"
using namespace std;

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class best_first_greedy : public SearchStateExplorer_GenericAlgo<T_Cost, T_State,
                        priority_queue<Types::node_type<T_Cost, T_State>,vector<Types::node_type<T_Cost, T_State>>,
                        Compare_H_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Cost, T_State,
                        priority_queue<Types::node_type<T_Cost, T_State>, vector<Types::node_type<T_Cost, T_State>>,
                        Compare_H_Cost>>;
        using typename base_type::problem_type;

        best_first_greedy(){
            this->frontier = new Min_H_Cost<T_Cost, T_State>();
        }
};