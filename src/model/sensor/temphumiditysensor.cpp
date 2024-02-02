#include "TempHumiditySensor.h"

TempHumiditySensor::TempHumiditySensor(std::string n, QTimer* t, std::string i) : AbstractSensor(n, t, i), temperature(0), humidity(0) {}

int TempHumiditySensor::getTemperature() const{
    return temperature;
}

unsigned int TempHumiditySensor::getHumidity() const{
    return humidity;
}

void TempHumiditySensor::setTemperature(int t){
    temperature=t;
}

void TempHumiditySensor::setHumidity(unsigned int h){
    humidity=h;
}

void TempHumiditySensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void TempHumiditySensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}
