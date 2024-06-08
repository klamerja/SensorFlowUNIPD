#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorMenu/SensorMenu.h"
#include "sensorMenu/ItemCard.h"
#include "../controller/Controller.h"

class Controller;
class SensorMenu;
class ItemCard;

enum sensorType {AirQuality, Electricity, Pressure, TemperatureHumidity};

class MainWindow : public QMainWindow{
private:
    Controller* controller;
    QMenuBar* menuBar;
    SensorMenu* sensorMenu;
    QWidget* panel;
    ItemCard* itemFocused;
    void createMenu();
    void setupUI();
public:
    explicit MainWindow(QWidget* parent=0);
    void removeFocusedItem();
    void addSensor(const QString&,int);
    void repaintSensorsList(std::vector<AbstractSensor*>);
    void deleteSensor(ItemCard*);
    void setHomePanel();
public slots:
    void newSensor();
    void removeSensor();
    void onItemClicked(ItemCard*);
    void searchWidgets(const QString& text) const;
};

#endif // MAINWINDOW_H