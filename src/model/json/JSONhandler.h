#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonDocument>
#include <QString>
#include <vector>
#include <QMap>

#include "../sensor/AbstractSensor.h"
#include "../sensor/IConstSensorHandler.h"

class JSONhandler : public IConstSensorHandler{
private:
    QJsonDocument* document;
    QString path;
public:
    JSONhandler(QString);
    std::vector<AbstractSensor*> getSensors(QTimer*) const;
    void addNewSensors(std::vector<AbstractSensor*>&);
    void handle(const AirQualitySensor*) override;
    void handle(const ElectricitySensor*) override;
    void handle(const PressureSensor*) override;
    void handle(const TempHumiditySensor*) override;
};

#endif // JSONHANDLER_H
