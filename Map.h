#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
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
        void fillLabrynth();
        void fillLeftSide();
        bool isValidPoint(int x, int y);
        bool outOfMinimumSeparation(int x, int y);
        bool toCloseToTheBox(int x, int y);
        bool isWall(int x, int y);
        int getNumberOfWalls();
        int getMapSize();
        void polishLabrynth();
        bool isAlley(int x, int y);
        void unlockAlley(int x, int y);
        void mirrorize();
        
    public:
        Map(int rows, int columns);
        void print();
};