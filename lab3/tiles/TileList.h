/*
 * This file contains the declaration of the mainwindow class.
 * See mainwindow.cpp for implementation of each member.
 */

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    TileList(); //Creates a new TileList object
    ~TileList(); //Destructor for TileList object
    void addTile(Tile tile); //Adds a Tile object to the array
    void drawAll(QGraphicsScene* scene); //Draws all the tiles
    int indexOfTopTile(int x, int y); //Finds the topmost Tile at x, y in the array
    void lower(int x, int y); //Lowers the topmost tile at x, y to the bottom
    void raise(int x, int y); //Raises the topmost tile at x, y to the top
    void remove(int x, int y); //Removes the topmost tile at x, y in the array
    void removeAll(int x, int y); //Removes all the tiles that contains x, y


private:
    int capacity = 10;
    int size = 0;
    Tile *tileList = new Tile[capacity];
    void checkResize(); //Checks if the array needs to be expanded 
};

#endif // TILELIST_H
