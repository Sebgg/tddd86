/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(Robot r);
    ~Junk() = default;
    /*
     * Draws this junk onto the given QGraphicsScene.
     */
    void draw(QGraphicsScene* scene) const override;
    /*
     * Overrides Unit's function so junk stays put.
     */
    void moveTowards(const Unit& u);

    /*
     * Overrides Unit's attack function so junk does not attack.
     */
    bool attacks(const Robot& t) const;

    /*
     * Overrides Robot's function to tell game it's junk.
     */
    bool isJunk() override;
};

#endif // JUNK_H
