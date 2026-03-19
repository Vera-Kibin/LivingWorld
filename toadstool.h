#ifndef TOADSTOOL_H
#define TOADSTOOL_H

#include "plant.h"
#include <vector>

class Toadstool : public Plant {
public:
    Toadstool(Tile* tile, std::vector<std::vector<Tile*>>* tiles,
              std::vector<Organism*>* organismsVector);

    void performTurn() override;
    void move();
    int getNutritionValue() const override { return -2; }
    bool isPoisonous() const override { return true; }
private:
    std::vector<std::vector<Tile*>>* worldTiles;
    std::vector<Organism*>* organismsVector;
    int turnsAlive = 0;

};

#endif // TOADSTOOL_H
