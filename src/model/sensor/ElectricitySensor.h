#ifndef ELECTRICITYSENSOR_H
#define ELECTRICITYSENSOR_H

#include "AbstractSensor.h"

class ElectricitySensor : public AbstractSensor{
private:
    double watt;
    double voltage;
public:
    ElectricitySensor(std::string, QTimer*, std::string);
    ~ElectricitySensor() =default;
    double getWatt() const;
    double getVoltage() const;
    void setWatt(double);
    void setVoltage(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
};

#endif // ELECTRICITYSENSOR_H
