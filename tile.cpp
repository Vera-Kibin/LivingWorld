#include "tile.h"
#include <QBrush>
#include <QColor>
#include <QtGui/qfont.h>
#include "organism.h"
#include <QFontMetrics>
#include <QtWidgets/qgraphicsscene.h>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "sheep.h"
#include "wolf.h"


Tile::Tile(int x, int y, int size, QGraphicsItem *parent)
    : QGraphicsRectItem(0, 0, size, size, parent), type(None)
{
    setPos(x, y);  //ustawienie kafelki osobno
    setBrush(Qt::gray);
}

void Tile::setType(TileType newType)
{
    type = newType;
    switch (type) {
    case Grass:
        setBrush(QColor(136, 189, 111));
        break;
    case Desert:
        setBrush(QColor(194, 178, 128));
        break;
    case Water:
        setBrush(QColor(75,151,220));
        break;
    case None:
        setBrush(Qt::gray);
        break;
    }
}

void Tile::addSymbol(QChar ch) {
    if (symbolText) {
        scene()->removeItem(symbolText);
        delete symbolText;
        symbolText = nullptr;
    }
    symbolText = new QGraphicsTextItem(QString(ch));
    symbolText->setDefaultTextColor(Qt::black);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(18);
    symbolText->setFont(font);


    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(ch);
    int textHeight = metrics.height();

    int tileSize = rect().width(); // zakładamy kwadrat

    QPointF center = this->scenePos() + QPointF((tileSize - textWidth) / 2, (tileSize - textHeight) / 2);
    symbolText->setPos(center);

    if (scene()) {
        scene()->addItem(symbolText);
    } else {
        qDebug() << "Symbol nie dodany – brak sceny!";

    }
    qDebug() << "scenePos:" << scenePos();
    qDebug() << "symbol setPos:" << center;
    qDebug() << "Dodaję symbol: " << ch << " unicode: " << ch.unicode();


}

Tile::TileType Tile::getType() const
{
    return type;
}
void Tile::setOrganism(Organism* org) {
    organism = org;
    update();
}

// void Tile::removeOrganism() {
//     organism = nullptr;
//     update();
// }
void Tile::removeOrganism() {
    organism = nullptr;
}
bool Tile::isFree() const {
    return organism == nullptr;
}

Organism* Tile::getOrganism() const {
    return organism;
}
void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mousePressEvent(event);
}

void Tile::removeSymbol() {
    if (symbolText) {
        scene()->removeItem(symbolText);
        delete symbolText;
        symbolText = nullptr;
    }

    // // usuw. organizm. z pamieci
    // if (organism) {
    //     delete organism;
    //     organism = nullptr;
    // }
}
void Tile::clearSymbol() {
    if (symbolText) {
        symbolText->setPlainText("");
    }
}
void Tile::removeOrganismCompletely() {
    if (symbolText) {
        scene()->removeItem(symbolText);
        delete symbolText;
        symbolText = nullptr;
    }

    organism = nullptr;
}
