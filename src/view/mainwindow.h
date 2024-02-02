#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorMenu/SensorMenu.h"
#include "../controller/Controller.h"

class Controller;
class SensorMenu;

class MainWindow : public QMainWindow{
private:
    Controller* controller;
    QMenuBar* menuBar;
    SensorMenu* sensorMenu;
    void createMenu();
    void setupUI();
public:
    explicit MainWindow(QWidget* parent=0);
};

#endif // MAINWINDOW_H
