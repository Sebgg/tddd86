#include "Cube.h"
#include "random.h"

Cube::Cube(){}

Cube::Cube(const char& letter) {
    letters = "";
    topSide = letter;
    visited = false;
}

Cube::Cube(const string& letters) {
    this->letters = letters;
    visited = false;
}

void Cube::setRandom(){
    int rand = randomInteger(0, 5);
    topSide = letters[rand];
}

void Cube::setVisited(){
    visited = !visited;
}

bool Cube::isVisited(){
    return visited;
}

char Cube::getTop(){
    return topSide;
}
