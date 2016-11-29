/*
 * This file contains the declaration of the tour class.
 * See tour.cpp for implementation of each member.
 */
#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    Tour(); //Creates a new Tour object.
    ~Tour(); //Destructor for tour object.
    void show(); //Displays the tour in standard output.
    void draw(QGraphicsScene* scene); //Draws the tour on display.
    int size(); //Calculates the number of nodes in the tour.
    double distance();  //Calculates the total distance of the tour.
    void insertNearest(Point p); //Heuristic. Puts new node to the closest node in the tour.
    void insertSmallest(Point p); //Heuristic. Puts the node where impact on distance is at a minimum.

private:
    void deleteTour(Node *curr, Node *head); //Deletes all nodes of the tour.
    Node *head;

};

#endif // TOUR_H
