#pragma once
#include "../../iterative_improvement_algorithms/genetic_operator.hpp"
#include "chess_problem.hpp"
#include "../../libraries/random.hpp"
#include <vector>
using namespace std;

class ChessOperator : public GeneticOperator<ChessState> {
public:
    //Costruisce un figlio partendo dai due genitori
    //xover_point è il punto in cui si divide il genoma 1 per inserire il genoma 2
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

    ChessState mutate(const ChessState& state) const override {
        vector<int> new_board = state.board;
        int pos     = random_int(0, (int)new_board.size() - 1);
        int new_col = random_int(0, state.N - 1);
        new_board[pos] = new_col;
        return ChessState(new_board);
    }

    bool is_solution(const ChessState& state) const override {
        return state.heuristic == 0;
    }

    int genome_size(const ChessState& state) const override {
        return state.N;
    }
};