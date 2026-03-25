#pragma once
#include "../../general/heuristic_state.hpp"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class ChessState : public Heuristic_State<int> {
    public:
        int N;
        vector<int> board;

        //N è la dim della scacchiera (NxN)
        //static_cast<int> è per evitare warning di conversione
        ChessState(const vector<int>& b) : N(static_cast<int>(b.size())), board(b)
        {
            heuristic = computeHeuristic(); //calcola i conflitti
            objective = (heuristic == 0);
            name = boardToString();
        }

        bool empty() const { return heuristic != 0; }

        bool operator>(const ChessState& other) const {
            return heuristic < other.heuristic;
        }

        void print() const {
            
            string sep = "+" + string(N * 2 + 1, '-') + "+";
            cout << sep << "\n";
            for (int row = 0; row < N; row++) {
                cout << "| ";
                for (int col = 0; col < N; col++)
                    cout << (board[col] == row ? "Q " : ". ");
                cout << "| h=" << heuristic << "\n";
            }
            cout << sep << "\n";
        }

        int computeHeuristic() const {
            int conflicts = 0;
            for (int col1 = 0; col1 < N - 1; col1++)
                for (int col2 = col1 + 1; col2 < N; col2++) {
                    int dist_col = abs(board[col1] - board[col2]); //controllo verticale 
                    int dist_row = abs(col1 - col2); //dist orizzontale tra le colonne
                    if (dist_col == 0 || dist_col == dist_row)   // stessa colonna O diagonale
                        conflicts++;
                }
            return conflicts;
        }

        string boardToString() const {
            string s;
            for (int i = 0; i < N; ++i) {
                s += to_string(board[i]);
                if (i < N - 1) s += ',';
            }
            return s;
        }
};