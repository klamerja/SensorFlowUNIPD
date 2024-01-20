#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include "abstractsensor.h"
#include <string>

class TempHumiditySensor : public AbstractSensor{
private:
    int temperature;
    short int humidity;
public:
    TempHumiditySensor(std::string);
    ~TempHumiditySensor() = default;
    int getTemperature() const;
    short int getHumidity() const;
    void setTemperature(int);
    void setHumidity(short int);

};

#endif // TEMPHUMIDITYSENSOR_H
