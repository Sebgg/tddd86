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
    /*Node *p = new Node(a);
    Node *q = new Node(b);
    Node *r = new Node(c);
    Node *s = new Node(d);
    head = p;
    p->next = q;
    q->next = r;
    r->next = s;
    s->next = p;*/
    head = nullptr;
}

Tour::~Tour()
{
    deleteNode(head->next, head);
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

}

void Tour::deleteNode(Node *curr, Node *head)
{
    if(curr == head){
        delete curr;
    } else {
        Node *nextNode = curr->next;
        //will this cause a collapse when reaching head again?
        //think edge-case:
        //curr->next = head value
        //goes into loop detects head and deletes curr.
        //collapses back here and deletes curr again?
        deleteNode(nextNode, head);
        delete curr;
    }
}
