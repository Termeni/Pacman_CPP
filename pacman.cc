#include <iostream>
#include "Map.h"

using namespace std;

int main() {
    
    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    Cell *c = new Cell('5');
    Cell c2 = Cell('5');
    
    cout << c->getValue() << endl;
    cout << c2.getValue() << endl;
    
    Map *map = new Map(11,11);
    map->print();
    
    cout << "printed map..." << endl;
    
    
    
    
    
    /*
    Cell c = Cell('5');
    
    Cell c2 = Cell();
    
    cout << c.getValue() << c2.getValue() << c.getValue() << endl;
    */
}