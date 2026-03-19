#include "wolf.h"
#include "dandelion.h"
#include "tile.h"
#include "sheep.h"
#include "toadstool.h"
#include <QDebug>
#include <QRandomGenerator>

    Wolf::Wolf(Tile* tile, std::vector<std::vector<Tile*>>* tiles)
    : Animal(tile), worldTiles(tiles)
{
    power = 8;
    initiative = 6;
    liveLength = 15;
    powerToReproduce = 10;
    qDebug() << "Konstruktor WILK: przypisuję znak";
    sign = 'W';
}

void Wolf::performTurn() {
    qDebug() << "Wilk wykonuje turę!";

    power++;
    liveLength--;

    if (liveLength <= 0) {
        qDebug() << "Wilk umarł ze starości!";
        die();
        return;
    }

    if (!tryToEat()) {
        move();
    }
}


bool Wolf::tryToEat() {
    if (!tile || !worldTiles || !isAlive()) return false;

    int r = tile->row;
    int c = tile->col;

    std::vector<std::pair<int, int>> directions = {
        {r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}
    };

    for (auto [newR, newC] : directions) {
        if (newR >= 0 && newR < static_cast<int>(worldTiles->size()) &&
            newC >= 0 && newC < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[newR][newC];

            if (dynamic_cast<Sheep*>(dest->getOrganism())) {
                // 🐺 Wilk zjada owcę!
                Organism* victim = dest->getOrganism();
                victim->die();  // usuń owcę z pola

                tile->clearSymbol();      // usuwa symbol z obecnego pola
                tile->setOrganism(nullptr);

                tile = dest;              // przechodzi na nowe pole
                tile->setOrganism(this);
                tile->addSymbol(getSign());

                power += 3; // wzmacnia sie po jedzeniu
                qDebug() << "Wilk zjadł owcę!";
                return true;
            }



        }
    }

    return false;
}


void Wolf::move() {
    if (!tile || !worldTiles) return;

    int r = tile->row;
    int c = tile->col;

    std::vector<std::pair<int, int>> directions = {
        {r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}
    };

    std::shuffle(directions.begin(), directions.end(), *QRandomGenerator::global());

    for (auto [nr, nc] : directions) {
        if (nr >= 0 && nr < static_cast<int>(worldTiles->size()) &&
            nc >= 0 && nc < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[nr][nc];

            if (dest->getType() == Tile::Grass && dest->isFree()) {
                tile->clearSymbol();
                tile->setOrganism(nullptr);

                tile = dest;
                tile->setOrganism(this);
                tile->addSymbol(getSign());

                return;
            }
        }
    }
}
