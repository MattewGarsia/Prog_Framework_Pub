#pragma once

#include "../../search_tree_algorithms/problem_state_explorer.hpp"
#include "../../general/heuristic_state.hpp"
#include "../../general/node.hpp"
#include "../../general/action.hpp"
#include "graphAction.hpp"
#include <map>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class graphProblem : public ProblemStateExplorer<double, Heuristic_State<double>> {
    public:
        using base_type = ProblemStateExplorer<double, Heuristic_State<double>>;
        using typename base_type::node_type;
        using typename base_type::state_type;
        using typename base_type::action_type;

        vector<node_type> node_list;
        map<string, node_type*> node_index;
        map<string, vector<action_type*>> adjacency_list; //ogni nodo viene associato alla lista delle azioni
        vector<unique_ptr<action_type>> action_list;

        graphProblem() : base_type(nullptr, {}) {}

        node_type* add_node(const string& name, double heuristic_value, bool objective = false) {
            Heuristic_State<double> h_state;
            h_state.name = name;
            h_state.objective = objective;
            h_state.heuristic = heuristic_value;

            node_list.emplace_back(h_state, nullptr, nullptr);
            node_type* node_ptr = &node_list.back();
            node_index[name] = node_ptr;
            return node_ptr;
        }

        void add_edge(const string& from_node, const string& to_node, double cost) {
            if(node_index.find(from_node) == node_index.end()) return;

            //prendo la destinazione, creo l'azione e la aggiungo alla lista delle azioni
            state_type dest = node_index[to_node]->current_state;
            graphAction* action = new graphAction(dest, cost);
            action_list.push_back(unique_ptr<graphAction>(action));

            //aggiungo l'azione alla lista
            adjacency_list[from_node].push_back(action);
        }

        vector<action_type*> get_actions(const state_type& current_state) const override {
            auto vect_actions = adjacency_list.find(current_state.name);
            if (vect_actions != adjacency_list.end()) {
                return vect_actions->second;
            }
            return {};
        }

        state_type get_result(const action_type& action) const override {
            return action.destination_state;
        }
};
