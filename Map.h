#include <list>
#include "Cell.h"

using namespace std;

class Map{
    private:
        list<list<Cell> > map;
    public:
        Map(int rows, int columns);
};