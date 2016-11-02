/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include<iostream>

using namespace std;

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot = new Robot();
        robots.push_back(robot);
        cout << "aids" << endl;
    }
    teleportHero();
    cout << "cancer" << endl;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    //for (size_t i = 0; i < junks.size(); ++i)
    //    junks[i].draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));

}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards(hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int x = 0;
    while (x < robots.size()) {
        bool collision = (countRobotsAt(*robots[x]) > 1);
        if (collision) {
            for( size_t i = 0; i < robots.size(); i++){
                if(robots[i]->at(*robots[x])){
                    robots[i] = (new Junk(*robots[i]));
                    numberDestroyed++;
                }
            }

        }
        x++;
    }
    cout << numberDestroyed << "ebola" << endl;
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    return (robots.size() != 0);
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit) || (robots[i]->at(unit) && robots[i]->isJunk())) return false;
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    bool empty = countRobotsAt(unit) == 0;
    for(size_t i = 0; i < robots.size(); i++){
        if(robots[i]->at(unit) && robots[i]->isJunk()){
            cout << "Poop" << endl;
            return false;
        }
    }
    return true && empty;
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit) && !robots[i]->isJunk()){
            count++;
        }
    }
    return count;
}
