#pragma once

template <typename T_Cost>
class Heuristic_State : public State<T_Cost>{
    public:
        T_Cost heuristic = T_Cost();
};