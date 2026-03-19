#include "sheep.h"
#include <QDebug>
#include <QRandomGenerator>
#include "tile.h"

Sheep::Sheep(Tile* tile, std::vector<std::vector<Tile*>>* tiles)
    : Animal(tile), worldTiles(tiles) {
    power = 5;
    initiative = 4;
    liveLength = 10;
    powerToReproduce = 8;
    qDebug() << "Konstruktor SHEEP: przypisuję znak";
    sign = 'S';
}

void Sheep::performTurn() {
    qDebug() << "Owca wykonuje turę!";

    power++;
    liveLength--;

    if (liveLength <= 0) {
        qDebug() << "Owca umarła ze starości!";
        die();
        return;
    }


    tryToReproduce();
    move();
}
void Sheep::move() {
    if (!tile || !worldTiles || !isAlive()) return;
    int r = tile->row;
    int c = tile->col;

    std::vector<std::pair<int, int>> directions = {
        {r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}
    };

    std::shuffle(directions.begin(), directions.end(), *QRandomGenerator::global());

    for (auto [newR, newC] : directions) {
        if (newR >= 0 && newR < static_cast<int>(worldTiles->size()) &&
            newC >= 0 && newC < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[newR][newC];

            if (dest->getType() == Tile::Grass && dest->isFree()) {

                //  Czysci tylko symbol, bez usuwania siebie
                tile->clearSymbol();
                tile->setOrganism(nullptr);  // oznacz. kafelk. jako wolny

                // Przejscie owcy na nowy kafelek
                tile = dest;
                tile->setOrganism(this);
                tile->addSymbol(getSign());

                return;
            }
        }
    }
}
void Sheep::tryToReproduce() {
    if (power < powerToReproduce) return;

    int r = tile->row;
    int c = tile->col;

    // sprawdzanie czy jest obok
    bool partnerNearby = false;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < static_cast<int>(worldTiles->size()) &&
                nc >= 0 && nc < static_cast<int>((*worldTiles)[0].size())) {

                Organism* neighbor = (*worldTiles)[nr][nc]->getOrganism();
                if (neighbor && dynamic_cast<Sheep*>(neighbor)) {
                    partnerNearby = true;
                    break;
                }
            }
        }
    }

    if (!partnerNearby) return;  //  jak brak partnera to nie rozmnaza się

    // szukanie wolnego mijsca na dziecko
    std::vector<std::pair<int, int>> directions = {
        {r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}
    };

    std::shuffle(directions.begin(), directions.end(), *QRandomGenerator::global());

    for (auto [newR, newC] : directions) {
        if (newR >= 0 && newR < static_cast<int>(worldTiles->size()) &&
            newC >= 0 && newC < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[newR][newC];

            if (dest->getType() == Tile::Grass && dest->isFree()) {
                Sheep* baby = new Sheep(dest, worldTiles);
                baby->setSign('S');
                dest->setOrganism(baby);
                dest->addSymbol(baby->getSign());

                power -= 3;
                qDebug() << "Owca rozmnożyła się z partnerem!";
                return;
            }
        }
    }
}
