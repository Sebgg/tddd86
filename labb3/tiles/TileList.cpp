// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
using namespace std;

TileList::TileList()
{
    tileList = new array<Tile, 10>;
}

TileList::~TileList()
{
    delete[] this->tileList;
}

void TileList::addTile(Tile tile)
{
    tileList->at(tileList->size()) = tile;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(unsigned int i = 0; i < tileList->size()-1; i++) {
        Tile tile = tileList->at(i);
        tile.draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for(int i = tileList->size()-1; i >= 0; i--){
        Tile temp = tileList->at(i);
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
        Tile found = tileList->at(index);
        for(unsigned int i = index+1; i < tileList->size(); i++){
            tileList[i-1] = tileList[i];
        }
        tileList->back() = found;
    }
}

void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        Tile found = tileList->at(index);
        for(int i = index; i > 0; i--){
            tileList[i] = tileList[i-1];
        }
        tileList->front() = found;
    }
}

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1 && index != tileList->size()-1){
        for(unsigned int i = index+1; i < tileList->size(); i++){
            tileList[i-1] = tileList[i];
        }
        tileList[(tileList->size())-1] = nullptr;
    }
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x, y) != -1){
        this->remove(x, y);
    }
}
