#ifndef ITEMCARD_H
#define ITEMCARD_H

#include <QWidget>
#include <string>

#include "../MainWindow.h"
#include "../../model/sensor/AbstractSensor.h"
#include "../../model/sensor/TempHumiditySensor.h"
#include "../../model/sensor/PressureSensor.h"
#include "../../model/sensor/ElectricitySensor.h"
#include "../../model/sensor/AirQualitySensor.h"
#include "../../model/sensor/IConstSensorHandler.h"

class ItemCard : public QWidget, public IConstSensorHandler{
private:
    AbstractSensor* sensor;
    MainWindow* app;
public:
    ItemCard(AbstractSensor*, MainWindow*);
    void handle(const AirQualitySensor*) override;
    void handle(const ElectricitySensor*) override;
    void handle(const PressureSensor*) override;
    void handle(const TempHumiditySensor*) override;
    void mousePressEvent(QMouseEvent*) override;
signals:
    void mousePressed();
};

#endif // ITEMCARD_H
