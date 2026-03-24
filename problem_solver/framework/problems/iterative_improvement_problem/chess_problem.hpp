#pragma once

#include "../../iterative_improvement_algorithms/problem_curr_pop.hpp"
#include "../../general/state.hpp"
#include "../../general/action.hpp"
#include "chess_state.hpp"
#include "../../libraries/random.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

class ChessProblem : public Problem_popul<int, ChessState> {
public:
    using base_type   = Problem_popul<int, ChessState>;
    using node_type   = typename base_type::node_type;
    using action_type = typename base_type::action_type;
    using state_type  = ChessState;

    int N;
    mutable mt19937 rng;

    ChessProblem(int n, int k = 10, unsigned seed = 0) : base_type()
    {
        N = n;
        this->k = k;
        this->initial_node = new node_type(makeInitialState(n));
        rng = mt19937(seed == 0 ? (unsigned)chrono::steady_clock::now().time_since_epoch().count() : seed);
        if (n <= 3) throw invalid_argument("N deve essere > 3");

        current_population.clear();
        for (int i = 0; i < k; i++) current_population.push_back(makeRandomState(n));
    }

    state_type get_result(const action_type& action) const override {
        return action.destination_state;
    }
   
    virtual state_type get_best_neighbor(const state_type& state) const override{
        state_type best_neighbor = state;
        for (int col = 0; col < N; col++) {
            for (int row = 0; row < N; row++) {
                if (row == state.board[col]) continue; // mossa nulla
                vector<int> new_board = state.board;
                new_board[col] = row;
                state_type neighbor(new_board);
                if (neighbor.heuristic < state.heuristic) best_neighbor = neighbor;
            }
        }
        return best_neighbor;
    }

    void printBoard(const state_type& s) const { s.print(); }
    bool isValid(const state_type& s)    const { return s.heuristic == 0; }

    state_type get_random_neighbor(const state_type& state) const override {
        int col = random_int(0, N - 1);
        int row;
        
        do
        {
            row = random_int(0, N - 1);
        }while (row == state.board[col]); // cerco mossa non nulla
        
        vector<int> new_board = state.board;
        new_board[col] = row;
        return state_type(new_board);
    }

    state_type get_random_state() const override {
        return makeRandomState(N);
    }

    state_type makeInitialState(int n) const {
        return makeRandomState(n);
    }

    state_type makeRandomState(int n)const {
        vector<int> new_board(n);
        iota(new_board.begin(), new_board.end(), 0); //riempio la board con 0,...,n-1
        shuffle(new_board.begin(), new_board.end(), this->rng); //shuffle della board
        return state_type(new_board);
    }
};