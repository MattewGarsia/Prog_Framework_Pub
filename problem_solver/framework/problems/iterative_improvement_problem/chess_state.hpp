#pragma once
#include "../../general/state.hpp"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class ChessState : public Heuristic_State<int> {
    public:
        int N;
        vector<int> board;

        ChessState(const vector<int>& b) : N(static_cast<int>(b.size())), board(b)
        {
            heuristic = _computeHeuristic();
            objective  = (heuristic == 0);
            name       = _boardToString();
        }

        bool empty() const { return heuristic != 0; }

        bool operator>(const ChessState& other) const {
            return heuristic < other.heuristic;
        }

        void print() const {
            string sep = "+" + string(N * 2 + 1, '-') + "+";
            cout << sep << "\n";
            for (int r = 0; r < N; ++r) {
                cout << "| ";
                for (int c = 0; c < N; ++c)
                    cout << (board[r] == c ? "Q " : ". ");
                cout << "| h=" << heuristic << "\n";
            }
            cout << sep << "\n";
        }

    private:
        int _computeHeuristic() const {
            int conflicts = 0;
            for (int r1 = 0; r1 < N - 1; r1++)
                for (int r2 = r1 + 1; r2 < N; r2++) {
                    int dc = abs(board[r1] - board[r2]);
                    int dr = abs(r1 - r2);
                    if (dc == 0 || dc == dr)   // stessa colonna O diagonale
                        conflicts++;
                }
            return conflicts;
        }

        string _boardToString() const {
            string s;
            for (int i = 0; i < N; ++i) {
                s += to_string(board[i]);
                if (i < N - 1) s += ',';
            }
            return s;
        }
};