#pragma once

#include "../../general/problem.hpp"
#include "../../general/state.hpp"
#include "../../general/action.hpp"
#include "chess_state.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>
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

    explicit ChessProblem(int n, int k = 10, unsigned seed = 0)
        : base_type(new node_type(_makeInitialState(n, seed)), {}, k), N(n)
    {
        if (n <= 3) throw invalid_argument("N deve essere > 3");

        mt19937 rng(seed == 0
            ? (unsigned)chrono::steady_clock::now().time_since_epoch().count()
            : seed + 1);
        current_population.clear();
        for (int i = 0; i < k; ++i)
            current_population.push_back(_makeRandomState(n, rng));
    }

    vector<action_type*> get_actions(const state_type& state) const override {
        vector<action_type*> actions;
        actions.reserve(N * (N - 1) / 2);
        for (int r1 = 0; r1 < N - 1; ++r1)
            for (int r2 = r1 + 1; r2 < N; ++r2) {
                vector<int> nb = state.board;
                swap(nb[r1], nb[r2]);
                actions.push_back(new action_type(ChessState(nb), 1));
            }
        return actions;
    }

    state_type get_result(const state_type&,
                          const action_type& action) const override {
        return action.destination_state;
    }

    void printBoard(const state_type& s) const { s.print(); }
    bool isValid(const state_type& s)    const { return s.heuristic == 0; }

private:
    static state_type _makeInitialState(int n, unsigned seed) {
        mt19937 rng(seed == 0
            ? (unsigned)chrono::steady_clock::now().time_since_epoch().count()
            : seed);
        return _makeRandomState(n, rng);
    }

    static state_type _makeRandomState(int n, mt19937& rng) {
        vector<int> b(n);
        iota(b.begin(), b.end(), 0);
        shuffle(b.begin(), b.end(), rng);
        return state_type(b);
    }
};