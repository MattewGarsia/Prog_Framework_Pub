#include "graphProblem.hpp"
#include "graphAction.hpp"
#include "graphState.hpp"

graphProblem::graphProblem(State* initial_state_in): Problem(initial_state_in){
    State* S  = new graphState("S", 7);
    State* A  = new graphState("A", 9);
    State* B  = new graphState("B", 3);
    State* C  = new graphState("C", 2);
    State* D  = new graphState("D", 4);
    State* E  = new graphState("E", 5);
    State* F  = new graphState("F", 3);
    State* G1 = new graphState("G1", 0); 
    State* G2 = new graphState("G2", 0); 
    State* J  = new graphState("J", 1);


    adjacency_list["S"] = {
        new graphAction(A, 2.0), 
        new graphAction(B, 7.0), 
        new graphAction(D, 5.0)
    };

    adjacency_list["A"] = { new graphAction(B, 4.0) };

    adjacency_list["B"] = { 
        new graphAction(C, 3.0), 
        new graphAction(G1, 9.0) 
    };

    adjacency_list["C"] = { 
        new graphAction(J, 5.0), 
        new graphAction(F, 2.0) 
    };

    adjacency_list["D"] = { 
        new graphAction(S, 8.0), 
        new graphAction(C, 3.0), 
        new graphAction(E, 3.0) 
    };

    adjacency_list["E"] = { new graphAction(G2, 7.0) };

    adjacency_list["F"] = { 
        new graphAction(D, 1.0), 
        new graphAction(G2, 4.0) 
    };

    adjacency_list["J"] = { new graphAction(G1, 3.0) };

    adjacency_list["G1"] = {};
    adjacency_list["G2"] = {};

}

std::vector<Action*> graphProblem::getActions(State* current_state) const{
    graphState* g_state = dynamic_cast<graphState*>(current_state);
    if(g_state != nullptr){
        auto iterator = adjacency_list.find(g_state->name);

        if(iterator != adjacency_list.end()){
            return iterator->second;
        }
    }
    return std::vector<Action*>();

    
}

// controlla poi se questa funzione va bene
State* graphProblem::result(State* start, Action* action) const{
    graphAction* g_action = dynamic_cast<graphAction*>(action);

    return g_action->destination_state;
    
}

bool graphProblem::isGoal(State* state) const{
    graphState* g_state = dynamic_cast<graphState*>(state);

    return (g_state->name == "G1" || g_state->name == "G2");
}