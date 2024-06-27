#ifndef ELECTRICITYSENSOR_H
#define ELECTRICITYSENSOR_H

#include "AbstractSensor.h"

class ElectricitySensor : public AbstractSensor{
private:
    double watt;
    int voltage;
    QLineSeries* wattVals;
    QLineSeries* voltageVals;
public:
    ElectricitySensor(std::string, QTimer*, int, std::string="");
    ~ElectricitySensor() =default;
    double getWatt() const;
    int getVoltage() const;
    QLineSeries* getWattVals() const;
    QLineSeries* getVoltageVals() const;
    void setWatt(double);
    void setVoltage(int);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) const override;
private slots:
    void onTimerTimeout() override;
};

#endif // ELECTRICITYSENSOR_H
