#include "toadstool.h"
#include "tile.h"
#include <QDebug>
#include <QRandomGenerator>

Toadstool::Toadstool(Tile* tile, std::vector<std::vector<Tile*>>* tiles,
                     std::vector<Organism*>* organisms)
    : Plant(tile), worldTiles(tiles), organismsVector(organisms)
{
    this->tile = tile;
    sign = 'T';
    power = 0;
    initiative = 0;
    liveLength = 20;
    powerToReproduce = 0;
    turnsAlive = 0;

    qDebug() << "Konstruktor TOADSTOOL: przypisuję znak";
}

void Toadstool::performTurn() {
    if (!tile) {
        qDebug() << "CRASH: Grzyb nie ma przypisanego tile!";
        return;
    }
    qDebug() << "Grzyb wykonuje turę 🍄";

    turnsAlive++;
    int r = tile->row;
    int c = tile->col;

    bool nearWater = false;

    // Sprawdz sąsiedztwo czy jest woda?
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; // pomiń siebie
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < static_cast<int>(worldTiles->size()) &&
                nc >= 0 && nc < static_cast<int>((*worldTiles)[0].size())) {

                if ((*worldTiles)[nr][nc]->getType() == Tile::Water) {
                    nearWater = true;
                }
            }
        }
    }

    // Jesli obok woda -> NIE rozrasta sie
    if (nearWater || turnsAlive % 5 != 0) {
        qDebug() << "Grzyb nie rozrasta się (obok woda lub nie czas)";
        return;
    }

    // Probuj sie rozsiac 8 kier.
    std::vector<std::pair<int, int>> directions;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            directions.emplace_back(r + dr, c + dc);
        }
    }

    std::shuffle(directions.begin(), directions.end(), *QRandomGenerator::global());

    for (auto [newR, newC] : directions) {
        if (newR >= 0 && newR < static_cast<int>(worldTiles->size()) &&
            newC >= 0 && newC < static_cast<int>((*worldTiles)[0].size())) {

            Tile* dest = (*worldTiles)[newR][newC];
            if (dest->getType() == Tile::Grass && dest->isFree()) {
                bool waterNearby = false;

                for (int dr2 = -1; dr2 <= 1; ++dr2) {
                    for (int dc2 = -1; dc2 <= 1; ++dc2) {
                        int rr = newR + dr2;
                        int cc = newC + dc2;

                        if (rr >= 0 && rr < static_cast<int>(worldTiles->size()) &&
                            cc >= 0 && cc < static_cast<int>((*worldTiles)[0].size())) {

                            if ((*worldTiles)[rr][cc]->getType() == Tile::Water) {
                                waterNearby = true;
                            }
                        }
                    }
                }

                if (waterNearby) {
                    qDebug() << "Odrzucono rozrost grzyba, obok woda";
                    continue;
                }

                Toadstool* newToad = new Toadstool(dest, worldTiles, organismsVector);
                newToad->setSign('T');
                dest->setOrganism(newToad);
                dest->addSymbol('T');
                organismsVector->push_back(newToad);
                qDebug() << "Grzyb urósł w: " << newR << "," << newC;
                break;
            }

        }
    }
}
