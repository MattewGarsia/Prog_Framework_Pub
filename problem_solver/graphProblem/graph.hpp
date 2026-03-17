#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>
#include "random.hpp"
#include "type.hpp"
using namespace std;

template <typename T_Type_State_Value, typename T_Type_Values = Types::cost_value_t>
class Graph {
    using node_type = Types::node_type<T_Type_State_Value, T_Type_Values>;
    using state_type = Types::state_type<T_Type_State_Value>;

    public:
        vector<node_type> nodes;
        int num_nodes;
        int max_depth;
        node_type* init_node;
        vector<node_type*> objectives;

        Graph(int _num_nodes, int _max_depth) {
            num_nodes  = _num_nodes;
            max_depth  = _max_depth;
            init_node  = nullptr;
        }

        void generate_random_graph() {
            nodes.clear();
            objectives.clear();

            if (num_nodes <= 0) { init_node = nullptr; return; }

            vector<T_Type_State_Value> unique_values;
            unique_values.reserve(num_nodes);
            for (int i = 0; i < num_nodes; i++) {
                unique_values.push_back(static_cast<T_Type_State_Value>(i + 1));
            }
            for (int i = num_nodes - 1; i > 0; i--) {
                int j = random_int(0, i);
                std::swap(unique_values[i], unique_values[j]);
            }

            nodes.reserve(num_nodes);
            for (int i = 0; i < num_nodes; i++) {
                node_type new_node;
                new_node.current_state.name = unique_values[i];
                new_node.current_state.objective = false;
                new_node.depth  = -1;  // non ancora calcolata
                new_node.cost = random_int(1, 10);
                new_node.parent_node = nullptr;
                nodes.push_back(new_node);
            }

            init_node = &nodes[0];
            init_node->depth = 0;

            vector<node_type*> current_level = { init_node };

            for (int d = 0; d < max_depth && !current_level.empty(); d++) {
                vector<node_type*> next_level;

                // Raccoglie i nodi non ancora assegnati a nessun livello
                vector<int> unassigned;
                for (int i = 0; i < num_nodes; i++) {
                    if (nodes[i].depth == -1)
                        unassigned.push_back(i);
                }

                if (unassigned.empty()) break;

                for (node_type* parent : current_level) {
                    if (unassigned.empty()) break;

                    int num_children = random_int(1, 3); // 1-3 figli
                    for (int j = 0; j < num_children && !unassigned.empty(); j++) {
                        // Sceglie un nodo non assegnato casuale
                        int pick = random_int(0, unassigned.size() - 1);
                        int idx  = unassigned[pick];
                        unassigned.erase(unassigned.begin() + pick);

                        nodes[idx].depth = d + 1;
                        nodes[idx].parent_node = parent;
                        next_level.push_back(&nodes[idx]);
                    }
                }
                current_level = next_level;
            }

            // I nodi rimasti senza depth li mettiamo a max_depth (foglie extra)
            for (int i = 0; i < num_nodes; i++) {
                if (nodes[i].depth == -1)
                    nodes[i].depth = max_depth;
            }

            // Crea obiettivi
            for (int i = 1; i < num_nodes; i++) {  // i=1: la radice non è obiettivo
                if (random_int(0, 4) == 0) {
                    nodes[i].current_state.objective = true;
                    objectives.push_back(&nodes[i]);
                }
            }

            if (objectives.empty()) {
                nodes[num_nodes - 1].cost = 0;
                nodes[num_nodes - 1].current_state.objective = true;
                objectives.push_back(&nodes[num_nodes - 1]);
            }

            draw_graph();
        }


        void draw_graph() {
            for (const auto& node : nodes) {
                cout << "Node " << node.current_state.name 
                     << " (Cost: " << node.cost 
                     << ", Depth: " << node.depth 
                     << ", Objective: " << (node.current_state.objective ? "Yes" : "No") 
                     << ")" << endl;
            }
            cout<<endl<<endl;
        }
};