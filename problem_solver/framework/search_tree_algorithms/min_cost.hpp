#pragma once
#include "search_state_explorer.hpp"
#include "../general/queuing_structures.hpp"
#include "../libraries/type.hpp"

template <typename T_Type_State_Value, typename T_Type_State = Heuristic_State<T_Type_State_Value>>
class min_cost : public SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                Compare_G_Cost>> {
    public:
        using base_type = SearchStateExplorer_GenericAlgo<T_Type_State_Value, T_Type_State,
                        priority_queue<Types::node_type<T_Type_State_Value, T_Type_State>,
                        vector<Types::node_type<T_Type_State_Value, T_Type_State>>,
                        Compare_G_Cost>>;
        using typename base_type::problem_type;
        using typename base_type::state_type;
        using typename base_type::node_type;

        min_cost(){
            this->frontier = new Min_G_Cost<T_Type_State_Value, T_Type_State>();
        }

};