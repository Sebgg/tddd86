//
//  life.cpp
//  Life
//
//  Created by Hampus Eriksson and Sebastian Grunditz on 2016-09-01.
//  Copyright © 2016 Hampus Eriksson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
// #include "../lib/StanfordCPPLib/grid.h"
// #include "../lib/lifeutil.h"
#include <string>


using namespace std;

void printGrid(const Grid<char> &grid, const int &nRows, const int &nCols);
void tick(Grid<char> &gridOrg, const int &nRows, const int &nCols);
void checkNeighbours(const int row, const int col, const Grid<char> &grid, int &cnt);
void perfomCommand(Grid<char> &grid, const char command, const int &nRows, const int &nCols, bool &playing);
void createGrid(Grid<char> &grid, int &nRows, int &nCols);
void animate(Grid<char> &grid, const int &nRows, const int &nCols);
void play(Grid<char> &grid, const int &nRows, const int &nCols);


void createGrid(Grid<char> &grid, int &nRows, int &nCols){
    /*Creates a grid based on the input textfile.*/

    string fileName;
    cout << "Grid input file name? " << endl;
    cin >> fileName;

    ifstream input;
    input.open(fileName);
    string gridText;
    int rowNum = 0;

    while(getline(input, gridText)) {
        if(rowNum == 0){ //Sets the row size
            nRows = stoi(gridText); //c++11 conversion from string to integer
        }
        else if(rowNum == 1){ //Sets the column size
            nCols = stoi(gridText); //c++11 conversion from string to integer
            grid.resize(nRows, nCols);
        }
        else if(rowNum <= nRows+1) {
            for(int col = 0; col < nCols; ++col){ //Iterate columns and fill with text
                grid[rowNum-2][col] = gridText[col];
            }
        }
        else{}

        ++rowNum;
    } //Closes while loop

    input.close();

}

void printGrid(const Grid<char>& grid, const int &nRows, const int &nCols) {
    /*Prints the grid in terminal.*/

    string gridPrint;
    for(int row = 0; row < nRows; ++row){
        for(int column = 0; column < nCols; ++column){
            gridPrint.push_back(grid.get(row, column));
        }
        gridPrint.append("\n");
    }
    cout << gridPrint << endl;
}


void tick(Grid<char> &gridOrg, const int &nRows, const int &nCols) {
    /*Updates the grid one cycle.*/

    Grid<char> gridCopy = gridOrg;
    int cnt = 0;

    for(int row = 0; row < nRows; ++row){
        for(int col = 0; col < nCols; ++col){
            checkNeighbours(row, col, gridOrg, cnt);
            if(cnt < 2 || cnt > 3){
                gridCopy.set(row, col, '-');
            }
            else if(cnt == 3){
                gridCopy.set(row, col, 'X');
            }
        }
    }
    gridOrg = gridCopy;
}

void checkNeighbours(const int row, const int col, const Grid<char> &grid, int &cnt) {
    /*Checks the neighbours of a given cell in the grid.*/

    cnt = 0;
    for(int r = row - 1; r < row + 2; ++r){
        for(int c = col - 1; c < col + 2; ++c){
            if(grid.inBounds(r, c) && grid.get(r, c) == 'X' && (r != row || c != col)){
                    ++cnt;
            }
        }
    }
}

void performCommand(Grid<char> &grid, const char command, const int &nRows, const int &nCols, bool &playing) {
    /*Evaluates the user input and performs correct command.*/

    if(command == 'a'){
        animate(grid, nRows, nCols);
    }
    else if(command == 't'){
        tick(grid, nRows, nCols);
        printGrid(grid, nRows, nCols);
    }
    else if(command == 'q'){
        cout << "Have a nice Life!" << endl;
        playing = false;
    }
    else{
        cout << "Invalid command." << endl;
    }
}

void animate(Grid<char> &grid, const int &nRows, const int &nCols){
    /*Ticks the grid automatically until the user manually terminates the program.*/

    while(true){
        tick(grid, nRows, nCols);
        printGrid(grid, nRows, nCols);
        pause(100);
        clearConsole();
    }
}

void play(Grid<char> &grid, const int &nRows, const int &nCols){
    /*Keeps the game running until the user terminates it with command 'q'.*/

    bool playing = true;
    while(playing) {
        char command;
        cout << "a)nimate, t)ick, q)uit? " << endl;
        cin >> command;
        performCommand(grid, command, nRows, nCols, playing);
    }
}


int main() {
    /*Main function, prints welcome message and calls correct functions.*/

    cout << "\nWelcome to the TDDD86 Game of Life, \n,"
         << "a simulation of the lifecycle of a bacteria colony. \n"
         << "Cells (X) live and die by the following rules: \n"
         << "- A cell with 1 or fewer neighbours dies.\n"
         << "- Locations with 2 neighbours remain stable. \n"
         << "- Locations with 3 neighbours will create life. \n"
         << "- A cell with 4 or more neighbours dies.\n\n" << endl;

    int nCols;
    int nRows;
    Grid<char> grid;

    createGrid(grid, nRows, nCols);
    printGrid(grid, nRows, nCols);
    play(grid, nRows, nCols);
    return 0;
}



