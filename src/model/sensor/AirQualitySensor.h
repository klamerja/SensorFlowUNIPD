#ifndef AIRQUALITYSENSOR_H
#define AIRQUALITYSENSOR_H

#include "AbstractSensor.h"

class AirQualitySensor : public AbstractSensor{
private:
    unsigned int co2;
    double pm25;
    double pm10;
public:
    AirQualitySensor(std::string, QTimer*, std::string);
    ~AirQualitySensor() =default;
    unsigned int getCo2() const;
    double getPm25() const;
    double getPm10() const;
    void setCo2(unsigned int);
    void setPm25(double);
    void setPm10(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
};

#endif // AIRQUALITYSENSOR_H
