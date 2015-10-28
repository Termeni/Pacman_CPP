#include "Map.h"

using namespace std;

Map::Map(int rows, int columns){
    list<list<Cell> >list_rows(rows);
    for (int i = 0; i < columns; i++) {
        Cell cell = Cell();
        list<Cell> list_columns(columns,cell);
        list_rows.push_back(list_columns);
    }
    this->map = list_rows;
}