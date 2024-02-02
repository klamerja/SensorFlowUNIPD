#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include "AbstractSensor.h"

class TempHumiditySensor : public AbstractSensor{
private:
    int temperature;
    unsigned int humidity;
public:
    TempHumiditySensor(std::string, QTimer*, std::string);
    ~TempHumiditySensor() =default;
    int getTemperature() const;
    unsigned int getHumidity() const;
    void setTemperature(int);
    void setHumidity(unsigned int);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
};

#endif // TEMPHUMIDITYSENSOR_H
