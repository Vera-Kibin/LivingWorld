#ifndef SHEEP_H
#define SHEEP_H

#include "animal.h"
#include "organism.h"
#include <vector>

class Sheep : public Animal {
public:
    Sheep(Tile* tile, std::vector<std::vector<Tile*>>* tiles);

    void performTurn() override;
    void move() override;
    void clearSymbol();
    void tryToReproduce();
    void setTile(Tile* t) { tile = t; }



private:
    std::vector<std::vector<Tile*>>* worldTiles;

};

#endif // SHEEP_H
