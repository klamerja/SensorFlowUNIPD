#ifndef ELECTRICITYSENSOR_H
#define ELECTRICITYSENSOR_H

#include "AbstractSensor.h"

class ElectricitySensor : public AbstractSensor{
private:
    double watt;
    int voltage;
    QSplineSeries* wattVals;
    QSplineSeries* voltageVals;
public:
    ElectricitySensor(std::string, QTimer*, std::string="");
    ~ElectricitySensor() =default;
    double getWatt() const;
    int getVoltage() const;
    QSplineSeries* getWattVals() const;
    QSplineSeries* getVoltageVals() const;
    void setWatt(double);
    void setVoltage(int);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // ELECTRICITYSENSOR_H
