#ifndef PLANT_H
#define PLANT_H

#include "organism.h"

class Plant : public Organism {
public:
    Plant(Tile* tile) : Organism(tile) {}
    virtual int getNutritionValue() const = 0;
    virtual bool isPoisonous() const { return false; }
};

#endif // PLANT_H
