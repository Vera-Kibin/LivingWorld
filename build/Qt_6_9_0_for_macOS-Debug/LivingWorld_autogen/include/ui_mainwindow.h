/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QPushButton *grassButton;
    QPushButton *desertButton;
    QPushButton *waterMeButton;
    QPushButton *waterAutoButton;
    QPushButton *nextTurnButton;
    QPushButton *addSheepButton;
    QPushButton *addWolfButton;
    QPushButton *addDandelionButton;
    QPushButton *addToadstoolButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(869, 688);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, 0, 861, 611));
        grassButton = new QPushButton(centralwidget);
        grassButton->setObjectName("grassButton");
        grassButton->setGeometry(QRect(40, 90, 101, 32));
        desertButton = new QPushButton(centralwidget);
        desertButton->setObjectName("desertButton");
        desertButton->setGeometry(QRect(160, 90, 101, 32));
        waterMeButton = new QPushButton(centralwidget);
        waterMeButton->setObjectName("waterMeButton");
        waterMeButton->setGeometry(QRect(40, 140, 101, 32));
        waterAutoButton = new QPushButton(centralwidget);
        waterAutoButton->setObjectName("waterAutoButton");
        waterAutoButton->setGeometry(QRect(160, 140, 101, 32));
        nextTurnButton = new QPushButton(centralwidget);
        nextTurnButton->setObjectName("nextTurnButton");
        nextTurnButton->setGeometry(QRect(90, 400, 131, 51));
        addSheepButton = new QPushButton(centralwidget);
        addSheepButton->setObjectName("addSheepButton");
        addSheepButton->setGeometry(QRect(40, 190, 101, 32));
        addWolfButton = new QPushButton(centralwidget);
        addWolfButton->setObjectName("addWolfButton");
        addWolfButton->setGeometry(QRect(160, 190, 101, 32));
        addDandelionButton = new QPushButton(centralwidget);
        addDandelionButton->setObjectName("addDandelionButton");
        addDandelionButton->setGeometry(QRect(40, 240, 101, 32));
        addToadstoolButton = new QPushButton(centralwidget);
        addToadstoolButton->setObjectName("addToadstoolButton");
        addToadstoolButton->setGeometry(QRect(160, 240, 101, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 869, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        grassButton->setText(QCoreApplication::translate("MainWindow", "GRASS", nullptr));
        desertButton->setText(QCoreApplication::translate("MainWindow", "DESERT", nullptr));
        waterMeButton->setText(QCoreApplication::translate("MainWindow", "WATER me", nullptr));
        waterAutoButton->setText(QCoreApplication::translate("MainWindow", "WATER auto", nullptr));
        nextTurnButton->setText(QCoreApplication::translate("MainWindow", "Next Turn", nullptr));
        addSheepButton->setText(QCoreApplication::translate("MainWindow", "SHEEP", nullptr));
        addWolfButton->setText(QCoreApplication::translate("MainWindow", "WOLF", nullptr));
        addDandelionButton->setText(QCoreApplication::translate("MainWindow", "DANDELION", nullptr));
        addToadstoolButton->setText(QCoreApplication::translate("MainWindow", "TOADSTOOL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
