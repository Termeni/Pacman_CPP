#include "Map.h"

using namespace std;

Map::Map(int rows, int columns){
    this->rows = rows;
    this->columns = columns;
    
    vector<vector<Cell> >vector_rows(rows);
    for (int i = 0; i < rows; i++) {
        vector<Cell> vector_columns(columns);
        for (int j = 0; j < columns; j++) {
            Cell *cell = new Cell();
            vector_columns[j]=*cell;
        }
        vector_rows[i] = vector_columns;
    }
    map = vector_rows;
    initialize();
}

void Map::initialize(){
   createOuterBox();
   createInnerBox();
}

void Map::createOuterBox(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(isOutterBorder(i,j))
                map[i][j].setValue('0');
        }
    }
}

bool Map::isOutterBorder(int i, int j){
    if(i==0 || j==0 || i==rows-1 || j==columns-1 )
        return true;
    else
        return false;
}

void Map::createInnerBox(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(isInnerBox(i,j))
                map[i][j].setValue('0');
        }
    }
}

bool Map::isInnerBox(int i, int j){
    if( isBoxUp(i,j) || isBoxLeft(i,j) || isBoxRight(i,j) || isBoxDown(i,j))
        return true;
    else
        return false;
}

bool Map::isBoxUp(int i, int j){
    if (i==rows/2 && j>columns/2-3 && j<columns/2+3 && j!=columns/2)
        return true;
    else
        return false;
}

bool Map::isBoxDown(int i, int j){
    if (i==rows/2+4 && j>columns/2-3 && j<columns/2+3)
        return true;
    else
        return false;
}
        
bool Map::isBoxLeft(int i, int j){
    if (j==columns/2-3 && i>rows/2-1 && i<rows/2+5)
        return true;
    else
        return false;
}

bool Map::isBoxRight(int i, int j){
    if (j==columns/2+3 && i>rows/2-1 && i<rows/2+5)
        return true;
    else
        return false;
}

void Map::print(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << map[i][j].getValue();
        }
        cout << endl;
    }
}