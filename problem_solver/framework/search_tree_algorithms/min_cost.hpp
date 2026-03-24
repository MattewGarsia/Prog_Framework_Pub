#pragma once
#include "search_state_explorer.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"

template <typename T_Cost, typename T_State = Heuristic_State<T_Cost>>
class min_cost : public SearchStateExplorer_GenericAlgo<T_Cost, T_State,
                priority_queue<Types::node_type<T_Cost, T_State>,vector<Types::node_type<T_Cost, T_State>>,
                Compare_G_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Cost, T_State,
                        priority_queue<Types::node_type<T_Cost, T_State>,vector<Types::node_type<T_Cost, T_State>>,
                        Compare_G_Cost>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        min_cost(){
            this->frontier = new Min_G_Cost<T_Cost, T_State>();
        }

};