#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
#include <QRandomGenerator>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include "tile.h"
#include "organism.h"
#include "sheep.h"
#include "wolf.h"
#include "dandelion.h"
#include "toadstool.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setGrass();   // funkcja do zielonych kafelków
    void setDesert();  // funkcja do pustynnych kafelków
    void addWaterAuto();
    void enableWaterDrawing();
    void nextTurn();
    void addSheep();
    void addWolf();
    void addDandelion();
    void addToadstool();
    void resetButtonStyles();


protected:
    void mousePressEvent(QMouseEvent *event) override; // do klikania kafelka

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<std::vector<Tile*>> tiles;
    int currentTurn = 0;


    bool waterDrawingEnabled = false;
    bool addingSheepMode = false;
    bool addingWolfMode = false;
    bool addingDandelionMode = false;
    bool addingToadstoolMode = false;



    int remainingWater = 0;
    Tile::TileType lastTerrainType_ = Tile::Grass;
    std::vector<Organism*> organisms;

};


#endif // MAINWINDOW_H
