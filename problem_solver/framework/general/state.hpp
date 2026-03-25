
#pragma once

#include <vector>
using namespace std;

template <typename T_Cost>
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

template<typename T_Cost>
ostream& operator<<(ostream& os, const State<T_Cost>& state) {
    os << state.name;
    return os;
}