#ifndef GRAPHPROBLEM_HPP
#define GRAPHPROBLEM_HPP

#include "../../general/problem.hpp"
#include "../../general/state.hpp"
#include "../../general/action.hpp"
#include "graphAction.hpp"
#include <map>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class graphProblem : public Problem<double, Heuristic_State<double>> {
    public:
        using base_type = Problem<double, Heuristic_State<double>>;
        using typename base_type::node_type;
        using typename base_type::state_type;
        using typename base_type::action_type;

    private:
        vector<node_type> node_storage;
        map<string, node_type*> node_index;
        map<string, vector<action_type*>> adjacency_list;
        vector<unique_ptr<action_type>> action_storage;

        node_type* add_node(const string& name, double heuristic_value, bool objective = false) {
            Heuristic_State<double> h_state;
            h_state.name = name;
            h_state.objective = objective;
            h_state.heuristic = heuristic_value;

            node_storage.emplace_back(h_state, nullptr, nullptr);
            node_type* node_ptr = &node_storage.back();
            node_index[name] = node_ptr;
            return node_ptr;
        }

        void add_edge(const string& from, const string& to, double cost) {
            auto to_it = node_index.find(to);
            if (to_it == node_index.end()) {
                return;
            }

            action_storage.push_back(make_unique<graphAction>(to_it->second->current_state, cost));
            adjacency_list[from].push_back(action_storage.back().get());
        }

    public:
        graphProblem()
            : base_type(nullptr, {}) {
            node_storage.reserve(10);

            add_node("S", 7, false);
            add_node("A", 9, false);
            add_node("B", 3, false);
            add_node("C", 2, false);
            add_node("D", 4, false);
            add_node("E", 5, false);
            add_node("F", 3, false);
            add_node("G1", 0, true);
            add_node("G2", 0, true);
            add_node("J", 1, false);

            this->initial_node = node_index["S"];
            this->objective_nodes = { node_index["G1"], node_index["G2"] };

            add_edge("S", "A", 2.0);
            add_edge("S", "B", 7.0);
            add_edge("S", "D", 5.0);
            add_edge("A", "B", 4.0);
            add_edge("B", "C", 3.0);
            add_edge("B", "G1", 9.0);
            add_edge("C", "J", 5.0);
            add_edge("C", "F", 2.0);
            add_edge("D", "S", 8.0);
            add_edge("D", "C", 3.0);
            add_edge("D", "E", 3.0);
            add_edge("E", "G2", 7.0);
            add_edge("F", "D", 1.0);
            add_edge("F", "G2", 4.0);
            add_edge("J", "G1", 3.0);

            adjacency_list["G1"] = {};
            adjacency_list["G2"] = {};
        }

        explicit graphProblem(const state_type& initial_state_in)
            : graphProblem() {
            auto it = node_index.find(initial_state_in.name);
            if (it != node_index.end()) {
                this->initial_node = it->second;
            }
        }

        vector<action_type*> get_actions(const state_type& current_state) const override {
            auto iterator = adjacency_list.find(current_state.name);
            if (iterator != adjacency_list.end()) {
                return iterator->second;
            }
            return {};
        }

        state_type get_result(const state_type& start, const action_type& action) const override {
            (void)start;
            return action.destination_state;
        }
};

#endif