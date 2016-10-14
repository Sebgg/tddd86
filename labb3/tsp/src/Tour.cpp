// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    clear();
}

Tour::~Tour()
{
    deleteNode(head);
}

void Tour::show()
{
    
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    // TODO: write this member
}

double Tour::distance()
{
    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}

void deleteNode(Node curr)
{
    if(curr->next == nullptr){
        delete curr;
    } else {
        curr = nodeList->next;
        deleteNode(curr);
        delete curr;
    }
}

void clear()
{
    current = tail = new Node(null, null);
    head = new Node(null, tail);
    size = 0;
}
