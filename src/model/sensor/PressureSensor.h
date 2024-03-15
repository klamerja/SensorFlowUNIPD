#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include <QSplineSeries>

#include "AbstractSensor.h"

class PressureSensor : public AbstractSensor{
private:
    double pressure;
    QSplineSeries* pressureVals;
public:
    PressureSensor(std::string, QTimer*, std::string="");
    ~PressureSensor() =default;
    double getPressure() const;
    QSplineSeries* getPressureVals() const;
    void setPressure(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // PRESSURESENSOR_H
