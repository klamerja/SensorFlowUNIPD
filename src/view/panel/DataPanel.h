#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include <QList>

#include "../../model/sensor/AbstractSensor.h"
#include "../../model/sensor/PressureSensor.h"
#include "../../model/sensor/TempHumiditySensor.h"
#include "../../model/sensor/ElectricitySensor.h"
#include "../../model/sensor/AirQualitySensor.h"
#include "../../model/sensor/IConstSensorHandler.h"

class DataPanel : public QWidget, public IConstSensorHandler{
private:
    QTimer* timer;
    QList<QChart*> charts;
public:
    DataPanel(AbstractSensor*,QTimer*);
    virtual void handle(const AirQualitySensor*) override;
    virtual void handle(const ElectricitySensor*) override;
    virtual void handle(const PressureSensor*) override;
    virtual void handle(const TempHumiditySensor*) override;
    ~DataPanel();
};

#endif // DATAPANEL_H

