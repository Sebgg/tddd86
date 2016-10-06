// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
using namespace TileList;
using namespace std;

TileList::TileList()
{
    array<Tile, 10> tileList;
}

TileList::~TileList()
{
    delete[] tileList;
}

void TileList::addTile(Tile tile)
{
    tileList[tileList.size()] = tile;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(auto const& tile : tileList) {
        tile.draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for(int i = tileList.size()-1; i >= 0; i--){
        if(tileList[i].contains(x, y)){
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
        for(int i = index+1; i < tileList.size(); i++){
            tileList[i-1] = tileList[i];
        }
        tileList.back() = found;
    }
}

void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        Tile found = tileList[index];
        for(int i = 1; i < index; i++){
            tileList[i] = tileList[i-1];
        }
        tileList.front() = found;
    }
}

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        lower(x, y); //To get the element to remove first in the array
        
    }
}

void TileList::removeAll(int x, int y)
{
    // TODO: write this member
}
