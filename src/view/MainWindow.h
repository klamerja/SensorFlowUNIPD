#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>

#include "sensorMenu/SensorMenu.h"
#include "sensorMenu/ItemCard.h"
#include "../controller/Controller.h"

class Controller;
class SensorMenu;
class ItemCard;

enum sensorType {AirQuality, Electricity, Pressure, TemperatureHumidity};

class MainWindow : public QMainWindow{
    Q_OBJECT
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
protected:
    bool event(QEvent* event) override;
public slots:
    void newSensor();
    void removeSensor();
    void onItemClicked(ItemCard*);
    void searchWidgets(const QString& text) const;
signals:
    void themeChanged();
};

#endif // MAINWINDOW_H