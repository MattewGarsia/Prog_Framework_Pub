#include "../../../search_tree_algorithms/problem_state_explorer.hpp"
#include "cell.hpp"
using namespace std;

class Grid : public ProblemStateExplorer<double, Cell>{
    public:
        vector<vector<Cell>> grid;
        string sequence;

        Grid(int n){
            grid.resize(n, vector<Cell>(n));
            for (int col = 0; col < grid.size(); col++){
                for (int row = 0; row < grid.size(); row++){
                    grid[col][row] = Cell(-1, col, row);
                }
            }
        }

        void place_state_in_grid(Cell state, int x, int y){
            grid[x][y] = state;
        }

        vector<Cell> contact(Cell state1){
            vector<Cell> contacts;
            for (Cell s : get_actions(state1)){
                if (s.index_in_sequence < 0) continue;
                if (sequence[s.index_in_sequence] == 'H' && sequence[state1.index_in_sequence] == 'H') contacts.push_back(s);
            }
            return contacts;
        }

        double compute_Heuristic(Cell state){
            for (int col = 0; col < grid.size(); col++){
                for (int row = 0; row < grid.size(); row++){
                    if (is_contact(grid[col][row],grid[col+1][row])){
                        grid[col+1][row].heuristic += 1;
                    }
                    if(is_contact(grid[col][row],grid[col][row+1])){
                        grid[col][row+1].heuristic += 1;
                    }
                }
            }
        }

        vector<Cell> get_actions(Cell state){
            vector<Cell> actions;
            if (grid[state.x+1][state.y].index_in_sequence < 0) actions.push_back(grid[state.x+1][state.y]);
            if (grid[state.x][state.y+1].index_in_sequence < 0) actions.push_back(grid[state.x][state.y+1]);
            if (grid[state.x-1][state.y].index_in_sequence < 0) actions.push_back(grid[state.x-1][state.y]);
            if (grid[state.x][state.y-1].index_in_sequence < 0) actions.push_back(grid[state.x][state.y-1]);
            return actions;
        }
};