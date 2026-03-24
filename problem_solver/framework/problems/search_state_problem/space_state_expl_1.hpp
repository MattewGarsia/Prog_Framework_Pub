#pragma once

//Esplorazione di spazi degli stati 2

#include "graphProblem.hpp"

class Space_State_Expl_1 : public graphProblem {
    public:
        using base_type = graphProblem;
        using typename base_type::state_type;
        using typename base_type::node_type;
        using typename base_type::action_type;

        Space_State_Expl_1() {
            node_list.reserve(10);

            this->add_node("S", 7, false);
            this->add_node("A", 9, false);
            this->add_node("B", 3, false);
            this->add_node("C", 2, false);
            this->add_node("D", 4, false);
            this->add_node("E", 5, false);
            this->add_node("F", 3, false);
            this->add_node("G1", 0, true);
            this->add_node("G2", 0, true);
            this->add_node("J", 1, false);

            this->initial_node = node_index["S"];
            this->objective_nodes = { node_index["G1"], node_index["G2"] };

            this->add_edge("S", "A", 2.0);
            this->add_edge("S", "B", 7.0);
            this->add_edge("S", "D", 5.0);
            this->add_edge("A", "B", 4.0);
            this->add_edge("B", "C", 3.0);
            this->add_edge("B", "G1", 9.0);
            this->add_edge("C", "J", 5.0);
            this->add_edge("C", "F", 2.0);
            this->add_edge("D", "S", 8.0);
            this->add_edge("D", "C", 3.0);
            this->add_edge("D", "E", 3.0);
            this->add_edge("E", "G2", 7.0);
            this->add_edge("F", "D", 1.0);
            this->add_edge("F", "G2", 4.0);
            this->add_edge("J", "G1", 3.0);

            this->adjacency_list["G1"] = {};
            this->adjacency_list["G2"] = {};
        }
};