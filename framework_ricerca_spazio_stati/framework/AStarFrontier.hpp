#ifndef ASTARFRONTIER_HPP
#define ASTARFRONTIER_HPP

#include "frontier.hpp"
#include <queue>
#include "graphState.hpp"

struct CompareEuristicPath {
    bool operator()(const Node* a, const Node* b) const {
        graphState* g_state_a = dynamic_cast<graphState*>(a->state);
        graphState* g_state_b = dynamic_cast<graphState*>(b->state);

        return (g_state_a->euristic + a->path_cost) > (g_state_b->euristic + b->path_cost); 
    }
};

class aStarFrontier: public Frontier{

    std::priority_queue<Node*, std::vector<Node*>, CompareEuristicPath> nodes;

    public:

        void insert(Node* node) override{
            nodes.push(node);
        }

        Node* remove() override{
            Node* node = nodes.top();
            nodes.pop();
            return node;
        }

        bool isEmpty() const override{
            return nodes.empty();
        }

        std::vector<Node*> toString() const override{
            std::vector<Node*> result;
            std::priority_queue<Node*, std::vector<Node*>, CompareEuristicPath> copy=nodes;
            while(!copy.empty()){
                result.push_back(copy.top());
                copy.pop();
            }
            return result;
        }
};

#endif