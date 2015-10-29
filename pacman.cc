#include <iostream>
#include "Map.h"

using namespace std;

int main() {
    
    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    Map *map = new Map(31,31);
    map->print();
    
    cout << "printed map..." << endl;
    
    
    /*
    Cell c = Cell('5');
    
    Cell c2 = Cell();
    
    cout << c.getValue() << c2.getValue() << c.getValue() << endl;
    */
}