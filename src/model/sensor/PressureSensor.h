#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include "AbstractSensor.h"

class PressureSensor : public AbstractSensor{
private:
    double pressure;
public:
    PressureSensor(std::string, QTimer*, std::string);
    ~PressureSensor() =default;
    double getPressure() const;
    void setPressure(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
};

#endif // PRESSURESENSOR_H
