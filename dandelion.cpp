#include "dandelion.h"
#include "tile.h"
#include <QDebug>
#include <QRandomGenerator>

Dandelion::Dandelion(Tile* tile, std::vector<std::vector<Tile*>>* tiles)
    : Plant(tile), worldTiles(tiles) {
    power = 0;
    initiative = 0;
    liveLength = 9999;
    powerToReproduce = 0;
    sign = 'D';
    qDebug() << "Konstruktor DANDELION: przypisuję znak";
}

void Dandelion::performTurn() {
    qDebug() << "Dandelion rozprzestrzenia się 🌼";

    int r = tile->row;
    int c = tile->col;

    std::vector<std::pair<int, int>> directions = {
        {r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}
    };

    std::shuffle(directions.begin(), directions.end(), *QRandomGenerator::global());

    for (auto [newR, newC] : directions) {
        if (newR >= 0 && newR < static_cast<int>(worldTiles->size()) &&
            newC >= 0 && newC < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[newR][newC];
            if (dest->getType() == Tile::Grass && dest->isFree()) {
                Dandelion* newPlant = new Dandelion(dest, worldTiles);
                newPlant->setSign('D');
                dest->setOrganism(newPlant);
                dest->addSymbol('D');
                qDebug() << "Dandelion zasiany w: " << newR << "," << newC;
                break;
            }
        }
    }
}

