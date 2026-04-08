#pragma once

using namespace std;

template<typename T_Cost, typename T_State>
class General_Node{
    public:
        using node_type = General_Node<T_Cost, T_State>;
        using action_type = Action<T_Cost, T_State>;

        T_State current_state;
        const action_type* action = nullptr;
        int depth = 0;
        T_Cost cost = 0;

        General_Node(T_State state_in, const action_type* action_in = nullptr, int _depth = 0, T_Cost _cost = T_Cost{}) 
                            : current_state(state_in), action(action_in), depth(_depth), cost(_cost) {}
};