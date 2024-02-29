#include "TempHumiditySensor.h"

TempHumiditySensor::TempHumiditySensor(std::string n, QTimer* t, std::string i) :
    AbstractSensor(n, t, i),
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

    temperature=randomGen->bounded(-10,35); //Gradi celsius
    humidity=randomGen->bounded(0,100); //

    temperatureVals->append(currentTime, temperature);
    if(temperatureVals->count()>20)temperatureVals->remove(0);

    humidityVals->append(currentTime, humidity);
    if(humidityVals->count()>20)humidityVals->remove(0);
}
