/*This file contains the implementation of the TileList class.
 *See TileList.h for comments about each member.
 */

#include "TileList.h"
using namespace std;

TileList::TileList()
{
    tileList = new Tile[capacity];
}

TileList::~TileList()
{
    delete[] this->tileList;
}

void TileList::addTile(const Tile tile)
{
    checkResize();
    tileList[size] = tile;
    size++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(unsigned int i = 0; i <= size; i++) {
        Tile tile = tileList[i];
        tile.draw(scene);
    }
}

int TileList::indexOfTopTile(const int x, const int y)
{
    for(int i = size; i >= 0; i--){
        Tile temp = tileList[i];
        if(temp.contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::raise(const int x, const int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        Tile found = tileList[index];
        for(unsigned int i = index+1; i <= size; i++){
            tileList[i-1] = tileList[i];
        }
        tileList[size] = found;
    }
}

void TileList::lower(const int x, const int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        Tile found = tileList[index];
        for(int i = index; i > 0; i--){
            tileList[i] = tileList[i-1];
        }
        tileList[0] = found;
    }
}

void TileList::remove(const int x, const int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1 && index != size){
        for(unsigned int i = index+1; i <= size; i++){
            tileList[i-1] = tileList[i];
        }
    }
    size--;
}

void TileList::removeAll(const int x, const int y)
{
    while(indexOfTopTile(x, y) != -1){
        this->remove(x, y);
    }
}

void TileList::checkResize()
{
    if(size == capacity){
        Tile* bigger = new Tile[capacity*2];
        for(int i = 0; i < size; i++){
            bigger[i] = tileList[i];
        }
        delete[] tileList;
        tileList = bigger;
        capacity = capacity*2;
    }
}
