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
    return value == CORRIDOR;
}

bool Cell::isWall(){
    return value == WALL;
}

void Cell::setWall(){
    this->value = WALL;
}

void Cell::setCorridor(){
    this->value = CORRIDOR;
}

void Cell::setFood(){
    this->value = FOOD;
}

bool Cell::hasFood(){
    return value == FOOD;
}