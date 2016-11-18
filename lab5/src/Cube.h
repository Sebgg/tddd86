#ifndef _cube_h
#define _cube_h

#include <string>

using namespace std;

class Cube
{
public:
    Cube();

    Cube(const string& letters);

    Cube(const char& letter);

    ~Cube() = default;

    void setRandom();

    void setVisited();

    bool isVisited();

    char getTop();
private:
    //Const
    bool visited;
    char topSide;
    string letters;

    //private helpfunctions
};

#endif // CUBE_H
