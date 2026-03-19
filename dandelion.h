#ifndef DANDELION_H
#define DANDELION_H

#include "plant.h"
#include <vector>

class Dandelion : public Plant {
public:
    Dandelion(Tile* tile, std::vector<std::vector<Tile*>>* tiles);
    void performTurn() override;
    int getNutritionValue() const override { return 3; }
    bool isPoisonous() const override { return false; }

private:
    std::vector<std::vector<Tile*>>* worldTiles;
};

#endif // DANDELION_H
