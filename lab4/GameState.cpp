/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>
#include <memory>

using namespace std;

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot *r = new Robot();
        while(!isEmpty(*r)){
            r->teleport();
        }
        robots.push_back(r);
    }
    teleportHero();
}

GameState::GameState(GameState& other){
    this->robots = other.robots;
    this->hero = other.hero;
}

GameState::~GameState(){
    delete[] this->robots;
    delete this->hero;
}

GameState& GameState::operator=(const GameState &gameState){
    for(Robot robot : robots){
        delete robot;
    }
    delete hero;
    for(size_t i = 0; i < gameState.robots.size(); i++){
        robots[i] = gameState.robots[i];
    }
    hero = gameState.getHero();
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); i++)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));

}

void GameState::moveRobots() {
    for (size_t i = 0; i < robots.size(); i++)
        robots[i]->moveTowards(hero);

}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int x = 0;
    while (x < robots.size()) {
        bool collision = (countRobotsAt(*robots[x]) > 1);
        if (collision) {
            numberDestroyed += makeJunk(x);
        }
        x++;
    }
    return numberDestroyed;
}

int GameState::makeJunk(const int& x){
    int numberDestroyed = 0;
    for(size_t i = 0; i < robots.size(); i++){
        if(robots[i]->at(*robots[x]) && !robots[i]->isJunk()){
            Junk *j = new Junk(*robots[i]);
            delete robots[i];
            robots[i] = j;
            numberDestroyed++;
        }
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for(size_t i = 0; i < robots.size(); i++){
        if(!robots[i]->isJunk()){
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit) || (robots[i]->at(unit) && !robots[i]->isJunk())) return false;
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
    for(size_t i = 0; i < robots.size(); i++){
        if(robots[i]->at(unit) && !robots[i]->isJunk()){
            cout << "Poop" << endl;
            return false;
        }
    }
    return true;
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit)){
            count++;
        }
    }
    return count;
}
