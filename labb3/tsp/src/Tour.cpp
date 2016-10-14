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
    head = nullptr;
}

Tour::~Tour()
{
    deleteNode(head);
}

void Tour::show()
{
    Node * curr = head->next;
    while(curr->next != nullptr){
        cout << curr->point.toString() << endl;
        curr = curr->next;
    }
    delete curr;
}

void Tour::draw(QGraphicsScene *scene)
{
    Node *curr = head->next;
    while(curr->next != nullptr){
        curr->point.draw(scene);
        curr = curr->next;
    }
    delete curr;
}

int Tour::size()
{
    int t_size;
    Node *curr = head->next;
    while(curr->next != nullptr){
        t_size += 1;
        curr = curr->next;
    }
    return t_size;
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

void deleteNode(Node *curr)
{
    if(curr->next == *head){
        delete curr;
    } else {
        curr = curr->next;
        deleteNode(curr);
        delete curr;
    }
}
