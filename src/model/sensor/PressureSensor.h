#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include <QLineSeries>

#include "AbstractSensor.h"

class PressureSensor : public AbstractSensor{
private:
    double pressure;
    QLineSeries* pressureVals;
public:
    PressureSensor(std::string, QTimer*, int, std::string="");
    ~PressureSensor() =default;
    double getPressure() const;
    QLineSeries* getPressureVals() const;
    void setPressure(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // PRESSURESENSOR_H
