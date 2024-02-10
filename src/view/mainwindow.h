#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorMenu/SensorMenu.h"
#include "sensorMenu/ItemCard.h"
#include "../controller/Controller.h"

//Nota per domani: includendo Item mi da errore

class Controller;
class SensorMenu;
class ItemCard;

class MainWindow : public QMainWindow{
private:
    Controller* controller;
    QMenuBar* menuBar;
    SensorMenu* sensorMenu;
    void createMenu();
    void setupUI();
public:
    explicit MainWindow(QWidget* parent=0);
public slots:
    void onItemClicked(ItemCard*);
};

#endif // MAINWINDOW_H
