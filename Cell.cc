#include "Cell.h"

Cell::Cell(){
    this->value = ' ';
}

Cell::Cell(char value){
    this->value = value;
}

void Cell::setId(int id){
    this->id = id;
}

int Cell::getId(){
    return this->id;
}

void Cell::setValue(char value){
    this->value = value;
}

char Cell::getValue(){
    return this->value;
}

bool Cell::isCorridor(){
    return value == ' ';
}

bool Cell::isWall(){
    return value == '0';
}

void Cell::setWall(){
    this->value = '0';
}

void Cell::setCorridor(){
    this->value = ' ';
}