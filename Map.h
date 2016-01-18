#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Cell.h"
#include "Graph.h"
#include "KeyboardKeys.h"

using namespace std;

class Map{
    private:
        int rows;
        int columns;
        
        int food;

        int RedGhostX, RedGhostY;
        int YellowGhostX, YellowGhostY;
        int GreenGhostX, GreenGhostY;

        vector<vector<Cell> > map;
        
        void initialize();
        void createOuterBox();
        bool isOutterBorder(int i, int j);
        void createInnerBox();
        
        bool isBoxUp(int i, int j);
        bool isBoxLeft(int i, int j);
        bool isBoxRight(int i, int j);
        bool isBoxDown(int i, int j);
        void fillLabrynth();
        void fillLeftSide();
        bool isValidPoint(int x, int y);
        bool outOfMinimumSeparation(int x, int y);
        bool toCloseToTheBox(int x, int y);
        bool isCorridor(int x, int y);
        void putFood();
        void putPacman();
        void putGhosts();
        bool isInsideBox(int x, int y);

        int getNumberOfCorridors();
        int getNumberOfWalls();
        int getMapSize();
        Graph* obtainGraph();
        void polishLabrynth();
        bool isAlley(int x, int y);
        void unlockAlley(int x, int y);
        void mirrorize();
        
    public:
        Map(int rows, int columns);
        int pacmanX, pacmanY;
        int BlueGhostX, BlueGhostY;
        void print();
        bool isWall(int x, int y);
        bool hasFood(int x, int y);
        bool isPacman(int x, int y);
        bool isInnerBox(int i, int j);
        void movePacman(int key);
        bool isBlueGhost(int i,int j);
        bool isGreenGhost(int i,int j);
        bool isRedGhost(int i,int j);
        bool isYellowGhost(int i,int j);
        void setCorridor(int x,int y);
        void setPacman(int x, int y, bool hungry);
        void setBlueGhost(int x, int y);
        bool isGhost(int x, int y);
        string get_map_string();
};
