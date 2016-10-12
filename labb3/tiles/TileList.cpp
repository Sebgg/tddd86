
// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

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

void TileList::addTile(Tile tile)
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

int TileList::indexOfTopTile(int x, int y)
{
    for(int i = size; i >= 0; i--){
        Tile temp = tileList[i];
        if(temp.contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
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

void TileList::lower(int x, int y)
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

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1 && index != size){
        for(unsigned int i = index+1; i <= size; i++){
            tileList[i-1] = tileList[i];
        }
    }
    size--;
}

void TileList::removeAll(int x, int y)
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
