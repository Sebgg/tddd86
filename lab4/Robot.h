/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();
    Robot(const Robot& r);
    virtual ~Robot() = default;
    /*
     * Draws Robot in game window.
     */
    virtual void draw(QGraphicsScene* scene) const;
    /*
     * Tells the game that robot is not junk.
     */
    virtual bool isJunk();

};

#endif // ROBOT_H
