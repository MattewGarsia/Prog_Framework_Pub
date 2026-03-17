#pragma once

#include "state.hpp"
using namespace std;

template<typename T_Type_Cost, typename T_Type_State>
class Action {
    public:
        using state_type = T_Type_State;
        
        state_type destination_state;
        T_Type_Cost cost;
        
        Action(state_type dest, T_Type_Cost c) : destination_state(dest), cost(c) {}
        
        T_Type_Cost getCost() const { 
            return cost; 
        }
};