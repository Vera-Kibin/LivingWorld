#ifndef WOLF_H
#define WOLF_H

#include "animal.h"
#include <vector>

class Wolf : public Animal {
public:
    Wolf(Tile* tile, std::vector<std::vector<Tile*>>* tiles);

    void performTurn() override;
    void move() override;

private:
    bool tryToEat();
    std::vector<std::vector<Tile*>>* worldTiles;
};

#endif // WOLF_H
