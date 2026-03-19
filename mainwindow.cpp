#include "mainwindow.h"
#include "./ui_mainwindow.h" // automatycznie generowany; awiera dostep do .ui
#include "sheep.h"

#include <QGraphicsScene> // scena
#include <QGraphicsRectItem> // kafelek
#include <QGraphicsView>
#include <QBrush>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicjalizacja sceny(tworzenie i przypisywanie ja do widuku)
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Parametry kafelków
    int tileSize = 40;
    int mapWidth = 10;
    int mapHeight = 10;

    // Przesunięcie kafelków
    int offsetX = 200;
    int offsetY = 0;

    // Przygotowywanie wektora tiles na kafelki
    tiles.resize(mapHeight);

    for (int row = 0; row < mapHeight; ++row) {
        tiles[row].resize(mapWidth);
        for (int col = 0; col < mapWidth; ++col) {
            Tile* tile = new Tile(offsetX + col * tileSize, offsetY + row * tileSize, tileSize);
            tile->row = row;
            tile->col = col;
            tile->setType(Tile::None);
            scene->addItem(tile);
            tiles[row][col] = tile;


        }
    }

    scene->setSceneRect(0, 0, offsetX + mapWidth * tileSize, offsetY + mapHeight * tileSize);
    //
    connect(ui->grassButton, &QPushButton::clicked, this, &MainWindow::setGrass);
    connect(ui->desertButton, &QPushButton::clicked, this, &MainWindow::setDesert);
    connect(ui->waterAutoButton, &QPushButton::clicked, this, &MainWindow::addWaterAuto);
    connect(ui->waterMeButton, &QPushButton::clicked, this, &MainWindow::enableWaterDrawing);
    connect(ui->addSheepButton, &QPushButton::clicked, this, [this]() {
        resetButtonStyles();
        ui->addSheepButton->setStyleSheet("background-color: lightgreen");

        addingSheepMode = true;
        addingWolfMode = false;
        addingDandelionMode = false;
        addingToadstoolMode = false;
    });

    connect(ui->addWolfButton, &QPushButton::clicked, this, [this]() {
        resetButtonStyles();
        ui->addWolfButton->setStyleSheet("background-color: lightblue");

        addingWolfMode = true;
        addingSheepMode = false;
        addingDandelionMode = false;
        addingToadstoolMode = false;
    });

    connect(ui->addDandelionButton, &QPushButton::clicked, this, [this]() {
        resetButtonStyles();
        ui->addDandelionButton->setStyleSheet("background-color: lightgreen");
        addingDandelionMode = true;
        addingWolfMode = false;
        addingSheepMode = false;
        addingToadstoolMode = false;
    });
    connect(ui->addToadstoolButton, &QPushButton::clicked, this, [this]() {
        resetButtonStyles();
        ui->addToadstoolButton->setStyleSheet("background-color: lightblue");
        addingToadstoolMode = true;
        addingSheepMode = false;
        addingWolfMode = false;
        addingDandelionMode = false;
    });

    connect(ui->nextTurnButton, &QPushButton::clicked, this, &MainWindow::nextTurn);



}

MainWindow::~MainWindow() // destruktor - usuwa automatycznie gui
{
    delete ui;
}
// void MainWindow::setGrass()
// {
//     QColor grassColor(136,189,111);
//     for (auto& row : tiles) {
//         for (auto* tile : row) {
//             tile->setBrush(grassColor); // trawa
//         }
//     }
// }
void MainWindow::setGrass()
{
    lastTerrainType_ = Tile::Grass;
    int rows = tiles.size();
    int cols = tiles[0].size();
    int total = rows * cols;
    remainingWater = static_cast<int>(total * 0.1); // 10% wody

    for (auto& row : tiles) {
        for (Tile* tile : row) {
            tile->setType(Tile::Grass);
        }
    }
}
void MainWindow::setDesert()
{
    lastTerrainType_ = Tile::Desert;
    int rows = tiles.size();
    int cols = tiles[0].size();
    int total = rows * cols;
    remainingWater = static_cast<int>(total * 0.08); // 8% wody

    for (auto& row : tiles) {
        for (Tile* tile : row) {
            tile->setType(Tile::Desert);
        }
    }

}


// void MainWindow::setDesert()
// {
//     QColor desertColor(194, 178, 128); // piaskowy
//     for (auto& row : tiles) {
//         for (auto* tile : row) {
//             tile->setBrush(desertColor); // pustynia
//         }
//     }
// }
void MainWindow::enableWaterDrawing()
{
    if (lastTerrainType_ == Tile::None) {
        qDebug() << "Najpierw wybierz typ terenu (Grass lub Desert)";
        return;
    }
    waterDrawingEnabled = true;
}

// void MainWindow::addWaterAuto()
// {
//     double percentage = 0.1; // 10% wody
//     int rows = tiles.size();
//     int cols = tiles[0].size();
//     int total = rows * cols;
//     int count = static_cast<int>(total * percentage);

//     std::vector<std::pair<int, int>> positions;
//     for (int r = 0; r < rows; ++r)
//         for (int c = 0; c < cols; ++c)
//             positions.emplace_back(r, c);

//     std::shuffle(positions.begin(), positions.end(), *QRandomGenerator::global());

//     for (int i = 0; i < count; ++i) {
//         int r = positions[i].first;
//         int c = positions[i].second;
//         tiles[r][c]->setBrush(Qt::blue);
//     }
// }

void MainWindow::addWaterAuto()
{
    if (lastTerrainType_ == Tile::None)
        return;

    // Reset starej wody
    for (auto& row : tiles) {
        for (auto* tile : row) {
            if (tile->getType() == Tile::Water)
                tile->setType(lastTerrainType_);
        }
    }

    // Przygotowanie danych
    double percentage = (lastTerrainType_ == Tile::Grass) ? 0.1 : 0.08;

    int rows = tiles.size();
    int cols = tiles[0].size();
    int total = rows * cols;
    int count = static_cast<int>(total * percentage);
    remainingWater = count;

    std::vector<std::pair<int, int>> candidates;

    // Zbier. kafelki nadające się na wodę
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Tile::TileType type = tiles[r][c]->getType();
            if (type != Tile::None && type != Tile::Water) {
                candidates.emplace_back(r, c);
            }
        }
    }

    std::shuffle(candidates.begin(), candidates.end(), *QRandomGenerator::global());

    //  Ustaw wodę i zmniejsz remainingWater
    int placed = 0;
    for (int i = 0; i < static_cast<int>(candidates.size()) && remainingWater > 0 && placed < count; ++i) {
        int r = candidates[i].first;
        int c = candidates[i].second;
        tiles[r][c]->setType(Tile::Water);
        remainingWater--;
        placed++;
    }
}


// void MainWindow::mousePressEvent(QMouseEvent *event)
// {
//     if (!waterDrawingEnabled) return;

//     QPointF pos = ui->graphicsView->mapToScene(event->pos());

//     for (auto& row : tiles) {
//         for (auto* tile : row) {
//             if (tile->contains(tile->mapFromScene(pos))) {
//                 tile->setBrush(Qt::blue);
//                 return;
//             }
//         }
//     }
// }
// void MainWindow::mousePressEvent(QMouseEvent *event)
// {
//     if (!waterDrawingEnabled) return;

//     QPointF pos = ui->graphicsView->mapToScene(event->pos());

//     for (auto& row : tiles) {
//         for (auto* tile : row) {
//             if (tile->contains(tile->mapFromScene(pos))) {
//                 Tile::TileType current = tile->getType();

//                 //
//                 if (current == Tile::None)
//                     return;

//                 if (current != Tile::Water && remainingWater > 0) {
//                     tile->setType(Tile::Water);
//                     remainingWater--;
//                 }
//                 else if (current == Tile::Water) {
//                     tile->setType(lastTerrainType_);  // powrot
//                     remainingWater++;
//                 }

//                 return;
//             }
//         }
//     }
// }
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint viewPos = ui->graphicsView->mapFrom(this, event->pos());
    QPointF scenePos = ui->graphicsView->mapToScene(viewPos);

    for (auto& row : tiles) {
        for (auto* tile : row) {
            if (tile->contains(tile->mapFromScene(scenePos))) {

                if (addingSheepMode && tile->getType() == Tile::Grass) {
                    if (tile->isFree()) {
                        Sheep* sheep = new Sheep(tile, &tiles);

                        sheep->setSign('S');
                        tile->setOrganism(sheep);
                        tile->addSymbol(sheep->getSign());
                        organisms.push_back(sheep);
                        qDebug() << "Dodano owcę";
                    } else if (dynamic_cast<Sheep*>(tile->getOrganism())) {
                        Organism* toDelete = tile->getOrganism();

                        tile->removeSymbol();           // usuń tekst
                        tile->setOrganism(nullptr);    // usuń z kafelka

                        auto it = std::find(organisms.begin(), organisms.end(), toDelete);
                        if (it != organisms.end()) {
                            organisms.erase(it);       // usuń z listy
                        }

                        toDelete->die();

                        qDebug() << "Usunięto owcę";
                    }

                    return;
                }

                // 🐺 Tryb dodawania wilka (toggle)
                if (addingWolfMode && tile->getType() == Tile::Grass) {
                    if (tile->isFree()) {
                        Wolf* wolf = new Wolf(tile, &tiles);
                        wolf->setSign('W');
                        tile->setOrganism(wolf);
                        tile->addSymbol(wolf->getSign());
                        organisms.push_back(wolf);
                        qDebug() << "Dodano wilka";
                    } else if (dynamic_cast<Wolf*>(tile->getOrganism())) {
                            Organism* toDelete = tile->getOrganism();

                            tile->removeSymbol();           // usuń tekst
                            tile->setOrganism(nullptr);    // usuń z kafelka

                            auto it = std::find(organisms.begin(), organisms.end(), toDelete);
                            if (it != organisms.end()) {
                                organisms.erase(it);       // usuń z listy
                            }

                            toDelete->die(); // oznacz jako martwy
                            qDebug() << "Usunięto wilka";
                        }

                    return; // też nie wyłączamy trybu
                }
                // 🌼 Tryb dodawania mlecz (toggle)
                if (addingDandelionMode && tile->getType() == Tile::Grass) {
                    if (tile->isFree()) {
                        Dandelion* dandelion = new Dandelion(tile, &tiles);
                        dandelion->setSign('D');
                        tile->setOrganism(dandelion);
                        tile->addSymbol(dandelion->getSign());
                        organisms.push_back(dandelion);
                        qDebug() << "Dodano mlecz";
                    } else if (dynamic_cast<Dandelion*>(tile->getOrganism())) {
                        tile->removeSymbol();
                        qDebug() << "Usunięto mlecz";
                    }
                    return; // też nie wyłączamy trybu
                }
                // 🍄 Tryb dodawania grzyba
                if (addingToadstoolMode && tile->getType() == Tile::Grass) {
                    if (tile->isFree()) {
                        Toadstool* toadstool = new Toadstool(tile, &tiles, &organisms);
                        toadstool->setSign('T');
                        tile->setOrganism(toadstool);
                        tile->addSymbol(toadstool->getSign());
                        organisms.push_back(toadstool);
                        qDebug() << "Dodano grzyb";
                    } else if (dynamic_cast<Toadstool*>(tile->getOrganism())) {
                        tile->removeSymbol();
                        qDebug() << "Usunięto grzyb";
                    }
                    return; // też nie wyłączamy trybu
                }
                // Tryb rysowania wody
                if (waterDrawingEnabled) {
                    Tile::TileType current = tile->getType();

                    if (current == Tile::None)
                        return;

                    if (current != Tile::Water && remainingWater > 0) {
                        tile->setType(Tile::Water);
                        remainingWater--;
                    }
                    else if (current == Tile::Water) {
                        tile->setType(lastTerrainType_);
                        remainingWater++;
                    }

                    return;
                }

                return;
            }
        }
    }
}


// void MainWindow::nextTurn() {
//     qDebug() << ">>> Tura nr" << currentTurn;

//     // Przejdź przez oryginalny wektor, iterując bez kopiowania
//     for (auto it = organisms.begin(); it != organisms.end(); ) {
//         Organism* org = *it;

//         if (org) {
//             org->performTurn();

//             // Jeśli organizm umarł (usunął się z kafelka)
//             if (org->getTile() == nullptr) {
//                 qDebug() << "Kasuję organizm:" << org->getSign();
//                 delete org;
//                 it = organisms.erase(it);
//                 continue;
//             }

//         }

//         ++it;
//     }

//     currentTurn++;
// }
void MainWindow::nextTurn() {
    qDebug() << ">>> Tura nr" << currentTurn;

    // 1 Kopia organizmów tylko na tę turę
    std::vector<Organism*> currentOrganisms = organisms;

    // 2 Każdy z nich wykonuje turę
    for (Organism* org : currentOrganisms) {
        if (org && org->isAlive()) {
            org->performTurn();
        }
    }

    // 3 Usuwa martwe organizmy z oryginalnej listy
    for (auto it = organisms.begin(); it != organisms.end(); ) {
        if ((*it)->getTile() == nullptr) {
            delete *it;
            it = organisms.erase(it);
        } else {
            ++it;
        }
    }

    currentTurn++;
    addingSheepMode = false;
    addingWolfMode = false;
    addingDandelionMode = false;
    addingToadstoolMode = false;
    resetButtonStyles();
}




void MainWindow::addSheep()
{
    // znajdź pierwszy wolny kafelek typu Grass
    for (auto& row : tiles) {
        for (Tile* tile : row) {
            if (tile->getType() == Tile::Grass && tile->isFree()) {
                Sheep* sheep = new Sheep(tile, &tiles);


                organisms.push_back(sheep);
                return;
            }
        }
    }
}
void MainWindow::addWolf() {
    for (auto& row : tiles) {
        for (Tile* tile : row) {
            if (tile->getType() == Tile::Grass && tile->isFree()) {
                Wolf* wolf = new Wolf(tile, &tiles);
                tile->setOrganism(wolf);
                tile->addSymbol(wolf->getSign());
                organisms.push_back(wolf);
                return;
            }
        }
    }
}
void MainWindow::addDandelion() {
    for (auto& row : tiles) {
        for (Tile* tile : row) {
            if (tile->getType() == Tile::Grass && tile->isFree()) {
                Dandelion* dandelion = new Dandelion(tile, &tiles);
                tile->setOrganism(dandelion);
                tile->addSymbol(dandelion->getSign());
                organisms.push_back(dandelion);
                return;
            }
        }
    }
}
void MainWindow::addToadstool() {
    for (auto& row : tiles) {
        for (Tile* tile : row) {
            if (tile->getType() == Tile::Grass && tile->isFree()) {
                Toadstool* toadstool = new Toadstool(tile, &tiles, &organisms);
                tile->setOrganism(toadstool);
                tile->addSymbol(toadstool->getSign());
                organisms.push_back(toadstool);
                return;
            }
        }
    }
}
void MainWindow::resetButtonStyles() {
    ui->addSheepButton->setStyleSheet("");
    ui->addWolfButton->setStyleSheet("");
    ui->addDandelionButton->setStyleSheet("");
    ui->addToadstoolButton->setStyleSheet("");
}
