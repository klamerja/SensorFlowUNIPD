#include "temphumiditysensor.h"

TempHumiditySensor::TempHumiditySensor(std::string n) : AbstractSensor(n), temperature(0), humidity(0){}

int TempHumiditySensor::getTemperature() const{
    return temperature;
}

short int TempHumiditySensor::getHumidity() const{
    return humidity;
}

void TempHumiditySensor::setTemperature(int t){
    temperature=t;
}

void TempHumiditySensor::setHumidity(short int h){
    humidity=h;
}
