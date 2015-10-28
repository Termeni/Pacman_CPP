#include <iostream>
//#include "Cell.h"
#include "Map.h"

using namespace std;

int main() {
    
    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    Cell c = Cell('5');
    
    Cell c2 = Cell();
    
    cout << c.getValue() << c2.getValue() << c.getValue() << endl;
    
}