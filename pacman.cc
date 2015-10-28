#include <iostream>
#include "Cell.h"

using namespace std;

int main() {
    
    cout << "Hello World!" << endl;
    
    Cell c = Cell('5');
    
    Cell c2 = Cell();
    
    cout << c.getValue() << c2.getValue() << c.getValue() << endl;
    
}