#ifndef SENSORMENU_H
#define SENSORMENU_H

#include <QWidget>

#include "../MainWindow.h"
#include "../../model/sensor/AbstractSensor.h"

class MainWindow;

class SensorMenu : public QWidget{
private:
    MainWindow* app;
    QWidget* sensorsContainer;
public:
    SensorMenu(MainWindow*);
    void paintSensors(std::vector<AbstractSensor*>);
private slots:
    void updateBackground();
};

#endif // SENSORMENU_H
