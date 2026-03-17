
#pragma once

#include <vector>
using namespace std;

template <typename T_Type_Cost>
class State{
    public:
        string name;
        bool objective = false;

        State() = default;
        virtual ~State() = default;

        bool is_objective(){
            return objective;
        }
};

template <typename T_Type_Cost>
class Heuristic_State : public State<T_Type_Cost>{
    public:
        T_Type_Cost heuristic = T_Type_Cost();
};

template<typename T_Type_Cost>
ostream& operator<<(ostream& os, const State<T_Type_Cost>& state) {
    os << state.name;
    return os;
}