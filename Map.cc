#include "Map.h"

using namespace std;

Map::Map(int rows, int columns){
    this->rows = rows;
    this->columns = columns;
    int id=0;
    vector<vector<Cell> >vector_rows(rows);
    for (int i = 0; i < rows; i++) {
        vector<Cell> vector_columns(columns);
        for (int j = 0; j < columns; j++) {
            Cell *cell = new Cell();
            cell->setId(id);
            vector_columns[j]=*cell;
            id +=1;
        }
        vector_rows[i] = vector_columns;
    }
    map = vector_rows;
    initialize();
}

void Map::initialize(){
   createOuterBox();
   createInnerBox();
   fillLabrynth();
}

void Map::createOuterBox(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(isOutterBorder(i,j))
                map[i][j].setWall();
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
                map[i][j].setWall();
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

void Map::fillLabrynth(){
    fillLeftSide();
    polishLabrynth();
    mirrorize();
}

void Map::fillLeftSide(){
    
    srand(time(NULL));
    int corridors = getNumberOfCorridors()-1;
    float walls = getNumberOfWalls();
    float size = getMapSize();
    float saturation;
    do{
        int randx = (rand() % rows);
        int randy = (rand() % (columns/2));
        if(isValidPoint(randx,randy)){
            map[randx][randy].setWall();
            Graph *graph = obtainGraph();
            //cout << "Pasillos: " << corridors << " Nodesconn: " << graph->connexNodes(map[1][1].getId()) << endl;
            if(corridors==graph->connexNodes(map[1][1].getId())){
                walls = walls + 1;
                corridors = corridors - 1;
            }else{
                map[randx][randy].setCorridor();
            }
        }
        saturation = walls/size;
        //cout << saturation << endl;
    }while(saturation<0.35);
}

bool Map::isValidPoint(int x, int y){
    if(outOfMinimumSeparation(x,y) || toCloseToTheBox(x,y) || isWall(x,y)){
        return false;   
    }else{
        return true;
    }
}

bool Map::outOfMinimumSeparation(int x, int y){
    if(x<2 || y<2 || x>=rows-2 || y>=columns/2 )
        return true;
    else
        return false;
}

bool Map::toCloseToTheBox(int x, int y){
    if( x>rows/2-2 && x<rows/2+6 && y>columns/2-5 && y<columns/2+4){
        return true;
    }else{
        return false;
    }
}

bool Map::isWall(int x, int y){
    return map[x][y].isWall();
}

int Map::getNumberOfCorridors(){
    int total = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(map[i][j].isCorridor())
                total = total + 1;
        }
    }
    return total;
}

int Map::getNumberOfWalls(){
    int total = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(map[i][j].isWall())
                total = total + 1;
        }
    }
    return total;
}

int Map::getMapSize(){
    return rows*columns;
}

Graph* Map::obtainGraph(){
    Graph *graph = new Graph(getMapSize());
    
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < columns-1; j++) {
            if(map[i][j].isCorridor()){
                if(map[i+1][j].isCorridor()){
                    graph->addEdge(map[i][j].getId(),map[i+1][j].getId());
                }
                if(map[i-1][j].isCorridor()){
                    graph->addEdge(map[i][j].getId(),map[i-1][j].getId());
                }
                if(map[i][j+1].isCorridor()){
                    graph->addEdge(map[i][j].getId(),map[i][j+1].getId());
                }
                if(map[i][j-1].isCorridor()){
                    graph->addEdge(map[i][j].getId(),map[i][j-1].getId());
                }
            }
        }
    }
    
    return graph;
}

void Map::polishLabrynth(){
    for (int i = 2; i < rows-2; i++) {
        for (int j = 2; j < columns/2; j++) {
            if(isAlley(i,j))
                unlockAlley(i,j);
        }
    }
    for (int i = rows-2; i > 2; i--) {
        for (int j = columns/2; j > 2; j--) {
            if(isAlley(i,j))
                unlockAlley(i,j);
        }
    }
}

bool Map::isAlley(int x, int y){
    int colindantWalls = 0;
    if(map[x+1][y].isWall())
        colindantWalls +=1;
    if(map[x-1][y].isWall())
        colindantWalls +=1;
    if(map[x][y+1].isWall())
        colindantWalls +=1;
    if(map[x][y-1].isWall())
        colindantWalls +=1;
    return colindantWalls>=3;
}

//TODO: S'ha de refinar un pelet
void Map::unlockAlley(int x, int y){
    if( map[x+1][y].isWall() && map[x-1][y].isWall()){
        map[x][y+1].setCorridor();
        map[x][y-1].setCorridor();
    }else{
        map[x+1][y].setCorridor();
        map[x-1][y].setCorridor();
    }
}

void Map::mirrorize(){
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            if(map[i][j].isWall())
                map[i][columns-1-j].setWall();
        }
    }
}

void Map::print(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << map[i][j].getValue();
        }
        cout << endl;
    }
}