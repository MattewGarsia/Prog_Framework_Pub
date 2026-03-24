#pragma once
//Esplorazione di spazi degli stati 2

#include "graphProblem.hpp"

class Space_State_Expl_2 : public graphProblem {
    public:
        using base_type = graphProblem;
        using typename base_type::state_type;
        using typename base_type::node_type;
        using typename base_type::action_type;

        Space_State_Expl_2() {
            node_list.reserve(11);

            this->add_node("S",  20, false);
            this->add_node("A",  16, false);
            this->add_node("B",  16, false);
            this->add_node("C",  14, false);
            this->add_node("D",  17, false);
            this->add_node("E",  15, false);
            this->add_node("H",   8, false);
            this->add_node("I",  12, false);
            this->add_node("J",  10, false);
            this->add_node("G1",  0, true);
            this->add_node("G2",  0, true);

            this->initial_node = node_index["S"];
            this->objective_nodes = { node_index["G1"], node_index["G2"] };

            this->add_edge("S", "A", 3.0);
            this->add_edge("S", "B", 3.0);
            this->add_edge("S", "D", 3.0);
            this->add_edge("A", "H", 8.0);
            this->add_edge("A", "E", 1.0);
            this->add_edge("B", "I", 3.0);  
            this->add_edge("B", "J", 5.0);
            this->add_edge("B", "C", 2.0);
            this->add_edge("D", "C", 2.0);
            this->add_edge("C", "S", 1.0);
            this->add_edge("C", "G2", 18.0);
            this->add_edge("E", "H", 7.0);
            this->add_edge("E", "D", 2.0);
            this->add_edge("H", "G1", 9.0);
            this->add_edge("I", "H", 4.0);
            this->add_edge("I", "A", 1.0);
            this->add_edge("J", "G2", 12.0);
            this->add_edge("G1", "E", 2.0);
            this->add_edge("G2", "B", 15.0);
            this->add_edge("G2", "C", 2.0);

            this->adjacency_list["G1"] = {};
            this->adjacency_list["G2"] = {};
        }
};