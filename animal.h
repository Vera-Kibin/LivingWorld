#ifndef ANIMAL_H
#define ANIMAL_H

#include "organism.h"

class Animal : public Organism {
protected:
    int age = 0;

public:
    Animal(Tile* tile) : Organism(tile) {}
    virtual void performTurn() override = 0;
    virtual void move() = 0;
};

#endif // ANIMAL_H
