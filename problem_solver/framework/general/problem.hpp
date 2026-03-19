

template <typename T_Cost, typename T_State>
class Problem {
    public:
        using node_type = Types::node_type<T_Cost, T_State>;
        using state_type = T_State;
        using action_type = Action<T_Cost, T_State>;

        node_type* initial_node = nullptr;
        vector<node_type*> objective_nodes;

        Problem(node_type* _initial_node, vector<node_type*> _objectives)
        {
            initial_node = _initial_node;
            objective_nodes = _objectives;
        }
        
        virtual vector<action_type*> get_actions(const state_type& state) const = 0;
        virtual state_type get_result(const state_type& state, const action_type& action) const = 0;
};

template <typename T_Cost, typename T_State>
class Problem_popul : public Problem<T_Cost, T_State>{
    public:
        using state_type = T_State;
        int k;
        vector<state_type> current_pop;

        Problem_popul(node_type* _initial_node, vector<node_type*> _objectives, int _k) : Problem<T_Cost, T_State>(_initial_node, _objectives), k(_k) {
            current_pop.push_back(_initial_node->current_state);
            this->initial_node = _initial_node;
            this->objective_nodes = _objectives;
            k = _k;
        }
};