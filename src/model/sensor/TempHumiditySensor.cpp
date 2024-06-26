#include "TempHumiditySensor.h"

TempHumiditySensor::TempHumiditySensor(std::string name, QTimer* timer, int dist, std::string id) :
    AbstractSensor(name, timer, dist, id),
    temperature(0),
    humidity(0),
    temperatureVals(new QLineSeries),
    humidityVals(new QLineSeries) {}

int TempHumiditySensor::getTemperature() const{
    return temperature;
}

int TempHumiditySensor::getHumidity() const{
    return humidity;
}

QLineSeries* TempHumiditySensor::getTemperatureVals() const{
    return temperatureVals;
}

QLineSeries* TempHumiditySensor::getHumidityVals() const{
    return humidityVals;
}

void TempHumiditySensor::setTemperature(int t){
    temperature=t;
}

void TempHumiditySensor::setHumidity(int h){
    humidity=h;
}

void TempHumiditySensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void TempHumiditySensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}

void TempHumiditySensor::onTimerTimeout(){
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();

    temperature=genIntVal(-10, 35);
    humidity=genIntVal(0,100);

    temperatureVals->append(currentTime, temperature);
    if(temperatureVals->count()>20)temperatureVals->remove(0);

    humidityVals->append(currentTime, humidity);
    if(humidityVals->count()>20)humidityVals->remove(0);
}
