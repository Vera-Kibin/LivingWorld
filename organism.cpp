#include "organism.h"
#include "tile.h"
#include <QDebug>

Organism::Organism(Tile* tile) : tile(tile) {
    //tile->setOrganism(this);
    //tile->addSymbol(getSign());
    qDebug() << "Konstruktor ORGANIZM";


}
Organism::~Organism() {
    qDebug() << "DESTRUKTOR ORGANIZM";
}
void Organism::die() {
    if (tile) {
        tile->removeSymbol();
        tile->setOrganism(nullptr);
        tile = nullptr;
    }
}
