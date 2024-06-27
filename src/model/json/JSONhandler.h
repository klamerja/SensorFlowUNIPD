#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonDocument>
#include <QString>
#include <vector>

#include "model/sensor/AbstractSensor.h"
#include "model/sensor/IConstSensorHandler.h"

class JSONhandler : public IConstSensorHandler{
private:
    QJsonDocument* document;
    QString path;
public:
    JSONhandler(QString);
    virtual ~JSONhandler() =default;
    std::vector<AbstractSensor*> getSensors(QTimer*) const;
    void updateJSON(std::vector<AbstractSensor*>&);
    void handle(const AirQualitySensor*) override;
    void handle(const ElectricitySensor*) override;
    void handle(const PressureSensor*) override;
    void handle(const TempHumiditySensor*) override;
};

#endif // JSONHANDLER_H
