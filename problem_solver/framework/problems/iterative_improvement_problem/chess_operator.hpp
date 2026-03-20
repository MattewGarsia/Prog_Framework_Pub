#pragma once
#include "../../iterative_improvement_algorithms/genetic_operator.hpp"
#include "chess_problem.hpp"
#include "../libraries/random.hpp"
#include <vector>
using namespace std;

class ChessOperator : public GeneticOperator<ChessState> {
public:
    ChessState crossover(const ChessState& p1, const ChessState& p2, int xover_point) const override {
        vector<int> child_board;
        child_board.insert(child_board.end(),
                           p1.board.begin(),
                           p1.board.begin() + xover_point);
        child_board.insert(child_board.end(),
                           p2.board.begin() + xover_point,
                           p2.board.end());
        return ChessState(child_board);
    }

    ChessState mutate(const ChessState& individual) const override {
        vector<int> b = individual.board;
        int pos     = random_int(0, (int)b.size() - 1);
        int new_col = random_int(0, individual.N - 1);
        b[pos] = new_col;
        return ChessState(b);
    }

    bool is_solution(const ChessState& individual) const override {
        return individual.heuristic == 0;
    }

    int genome_size(const ChessState& individual) const override {
        return individual.N;
    }
};