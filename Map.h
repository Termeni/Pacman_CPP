#include <vector>
#include <iostream>
#include "Cell.h"

using namespace std;

class Map{
    private:
        int rows;
        int columns;
        vector<vector<Cell> > map;
        
        void initialize();
        void fill();
        
        
    public:
        Map(int rows, int columns);
        void print();
};