#include "Cell.h"

Cell::Cell(){
    this->value = ' ';
}

Cell::Cell(char value){
    this->value = value;
}

void Cell::setValue(char value){
    this->value = value;
}

char Cell::getValue(){
    return this->value;
}