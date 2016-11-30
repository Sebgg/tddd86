#ifndef CUBE_H
#define CUBE_H

#include <string>

using namespace std;

class Cube
{
public:

    /*
     * Cube constructor
     */
    Cube();

    /*
     * Cube constructor
     */
    Cube(const string& letters);

    /*
     * Cube constructor
     */
    Cube(const char& letter);

    /*
     * Cube destructor
     */
    ~Cube() = default;

    /*
     * Set random letter in cube to top side
     */
    void setRandom();

    /*
     * Flips the value of visited
     */
    void setVisited();

    /*
     * Return whether cube is visited or not
     */
    bool isVisited();

    /*
     * Return the top side of cube
     */
    char getTop();

private:
    //Const
    bool visited;
    char topSide;
    string letters;

    //private helpfunctions
};

#endif // CUBE_H
