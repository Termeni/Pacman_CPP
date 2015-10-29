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
        void createOuterBox();
        bool isOutterBorder(int i, int j);
        void createInnerBox();
        bool isInnerBox(int i, int j);
        bool isBoxUp(int i, int j);
        bool isBoxLeft(int i, int j);
        bool isBoxRight(int i, int j);
        bool isBoxDown(int i, int j);
        
    public:
        Map(int rows, int columns);
        void print();
};