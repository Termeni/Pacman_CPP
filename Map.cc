#include "Map.h"

using namespace std;

Map::Map(int rows, int columns){
    this->rows = rows;
    this->columns = columns;
    
    vector<vector<Cell> >vector_rows(rows);
    for (int i = 0; i < rows; i++) {
        vector<Cell> vector_columns(columns);
        for (int j = 0; j < columns; j++) {
            Cell cell = Cell();
            vector_columns.push_back(cell);
        }
        vector_rows.push_back(vector_columns);
    }
    this->map = vector_rows;
    cout << "ALAHAHAH" << endl;
    //this->fill();
    cout << "ALAHAHAH" << endl;
}

void Map::fill(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "ALAHAHAH" << endl;
            this->map[i][j].setValue('0');
        }
    }
}

void Map::print(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << this->map[i][j].getValue() << endl;
        }
    }
}