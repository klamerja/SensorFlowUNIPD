#ifndef ITEMCARD_H
#define ITEMCARD_H

#include <QFrame>
#include <string>

#include "../MainWindow.h"
#include "../../model/sensor/AbstractSensor.h"
#include "../../model/sensor/TempHumiditySensor.h"
#include "../../model/sensor/PressureSensor.h"
#include "../../model/sensor/ElectricitySensor.h"
#include "../../model/sensor/AirQualitySensor.h"
#include "../../model/sensor/IConstSensorHandler.h"

class MainWindow;

class ItemCard : public QFrame, public IConstSensorHandler{
    Q_OBJECT //A quanto pare, serve per implementare segnali propri quando implementati su una classe di QT
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
    void itemClicked(ItemCard*);
};

#endif // ITEMCARD_H
