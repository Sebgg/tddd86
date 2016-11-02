#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

/**/
Tour::Tour()
{
    head = nullptr;
}

Tour::~Tour()
{
    deleteTour(head->next, head);
}

void Tour::show()
{
    if(head != nullptr){
        cout << head->point.toString() << endl;
        Node *curr = head->next;
        while(curr != head){
            cout << curr->point.toString() << endl;
            curr = curr->next;
        }
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    if(head != nullptr){
        head->point.draw(scene);
        head->point.drawTo(head->next->point, scene);
        Node *curr = head->next;
        while(curr != head){
            curr->point.draw(scene);
            curr->point.drawTo(curr->next->point, scene);
            curr = curr->next;
        }
    }
}

int Tour::size()
{
    if(head != nullptr){
        int t_size = 1;
        Node *curr = head->next;
        while(curr != head){
            t_size += 1;
            curr = curr->next;
        }
        return t_size;
    }
    return -1;
}

double Tour::distance()
{
    if(head != nullptr){
        double totalDistance = head->point.distanceTo(head->next->point);;
        Node *curr = head->next;
        while(curr != head){
            totalDistance += curr->point.distanceTo(curr->next->point);
            curr = curr->next;
        }
        return totalDistance;
    }
    return -1;
}


void Tour::insertNearest(Point p)
{
    if(head == nullptr){
        Node *newNode = new Node(p);
        newNode->next = newNode;
        head = newNode;
    }
    else{
        Node *nearestNode = head;
        Node *curr = head->next;
        double shortestDistance = nearestNode->point.distanceTo(p);
        while(curr != head){
           double currDistance = p.distanceTo(curr->point);
           if(currDistance < shortestDistance){
               nearestNode = curr;
               shortestDistance = currDistance;
           }
           curr = curr->next;
        }
        Node *newNode = new Node(p);
        newNode->next = nearestNode->next;
        nearestNode->next = newNode; 
    }
}

void Tour::insertSmallest(Point p)
{
    Node *newNode = new Node(p);

    if(head == nullptr){
        newNode->next = newNode;
        head = newNode;
    }
    else{
        Node *nearestNode = head;
        Node *curr = head->next;

        double currDistance = 0;
        double origDistance = nearestNode->point.distanceTo(curr->point);
        double minDistance = nearestNode->point.distanceTo(newNode->point)
                + newNode->point.distanceTo(curr->point);
        minDistance -= origDistance;

        while(curr != head){
            origDistance = curr->point.distanceTo(curr->next->point);
            newNode->next = curr->next;
            curr->next = newNode;

            currDistance = curr->point.distanceTo(newNode->point)
                    + newNode->point.distanceTo(newNode->next->point);
            currDistance -= origDistance;

            if(currDistance < minDistance){
               minDistance = currDistance;
               nearestNode = curr;
            }
            curr->next = newNode->next;
            curr = curr->next;
        }
        newNode->next = nearestNode->next;
        nearestNode->next = newNode;
    }
}

void Tour::deleteTour(Node *curr, Node *head)
{
    if(curr == head){
        delete curr;
    } else {
        Node *nextNode = curr->next;
        deleteTour(nextNode, head);
        delete curr;
    }
}


