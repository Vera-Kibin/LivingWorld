#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QColor>
class Organism;

class Tile : public QGraphicsRectItem {
public:
    enum TileType { None, Grass, Desert, Water };

    Tile(int x, int y, int size, QGraphicsItem *parent = nullptr);

    void setType(TileType type);
    TileType getType() const;

    //
    void setOrganism(Organism* org);
    void removeOrganism();
    bool isFree() const;
    Organism* getOrganism() const;
    void addSymbol(QChar ch);
    void removeSymbol();
    void clearSymbol();
    void removeOrganismCompletely();

    int row = 0;
    int col = 0;
private:
    TileType type;
    Organism* organism = nullptr;
    QGraphicsTextItem* symbolText = nullptr;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // TILE_H
