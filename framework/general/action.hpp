#pragma once

#include "state.hpp"
using namespace std;

template<typename T_Cost, typename T_State>
class Action {
    public:
        using state_type = T_State;
        
        state_type destination_state;
        T_Cost cost;
        
        Action(state_type dest, T_Cost c){
            destination_state = dest;
            cost = c;
        }
        
        T_Cost getCost() const { 
            return cost; 
        }
};