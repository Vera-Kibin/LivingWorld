#ifndef ORGANISM_H
#define ORGANISM_H

#include <QChar>
class Tile;

class Organism {
protected:
    int power;
    int initiative;
    int liveLength;
    int powerToReproduce;
    QChar sign;
    Tile* tile;

public:
    Organism(Tile* tile);
    virtual ~Organism();

    virtual void performTurn() = 0;
    virtual QChar getSign() const { return sign; }
    virtual void setSign(QChar c) { sign = c; }
    virtual int getInitiative() const { return initiative; }

    Tile* getTile() const { return tile; }
    void setTile(Tile* t) { tile = t; }

    bool isAlive() const { return tile != nullptr; }
    void die();
};

#endif // ORGANISM_H
