#include "../../../general/state.hpp"
using namespace std;

class Cell : public HeuristicState<double>{
    public:
        int index_in_sequence;
        int x;
        int y;

        Cell(int _index_in_sequence, int _x, int _y){
            index_in_sequence = _index_in_sequence;
            x = _x;
            y = _y;
        }
};