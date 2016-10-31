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
    deleteNode(head, head);
}

void Tour::show()
{
    Node *curr = head;
    while(curr->next != head){
        cout << curr->point.toString() << endl;
        curr = curr->next;
    }
    //delete curr;
}

void Tour::draw(QGraphicsScene *scene)
{
    Node *curr = head;
    while(curr->next != head){
        curr->point.draw(scene);
        curr = curr->next;
    }
    //delete curr;
}

int Tour::size()
{
    int t_size = 0;
    Node *curr = head;
    while(curr->next != head){
        t_size += 1;
        curr = curr->next;
    }
    return t_size;
}

double Tour::distance()
{
    double totalDistance = 0;
    Node *curr = head;
    while(curr->next != head){
        totalDistance += curr->point.distanceTo(curr->next->point);
    }
    return totalDistance;
}


void Tour::insertNearest(Point p)
{
    Node *curr = head;

    if(curr == nullptr){
        Node *newNode = new Node(p);
        newNode->next = newNode;
        head = newNode; //Do I need a reference to head?
        cout << newNode->point.toString() << endl;
    }
    else{
        Node *nearestNode = curr;
        double smallestDistance = 0;
        while(curr->next != head){
           double currDistance = p.distanceTo(curr->point);
           if(currDistance < smallestDistance || smallestDistance == 0){
               nearestNode = curr;
               smallestDistance = currDistance;
           }
           curr = curr->next;
        }
        Node* tempPtr = nearestNode->next;
        Node *newNode = new Node(p);
        newNode->next = tempPtr;
        nearestNode->next = newNode;
        newNode->point.drawTo(nearestNode->point, scene);
        cout << newNode->point.toString() << endl;
    }
}

void Tour::insertSmallest(Point p)
{

}

void Tour::deleteNode(Node *curr, Node *head)
{
    if(curr->next == head){
        delete curr;
    } else {
        curr = curr->next;
        //will this cause a collapse when reaching head again?
        //think edge-case:
        //curr->next = head value
        //goes into loop detects head and deletes curr.
        //collapses back here and deletes curr again?
        deleteNode(curr, head);
        delete curr;
    }
}
