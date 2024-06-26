#include "AirQualitySensor.h"

#include <QList>

AirQualitySensor::AirQualitySensor(std::string name, QTimer* timer, int dist, std::string id) :
    AbstractSensor(name, timer, dist, id),
    co2(0),
    pm25(0),
    pm10(0),
    co2Vals(new QLineSeries),
    pm25Vals(new QLineSeries),
    pm10Vals(new QLineSeries) {}

int AirQualitySensor::getCo2() const{
    return co2;
}

double AirQualitySensor::getPm25() const{
    return pm25;
}

double AirQualitySensor::getPm10() const{
    return pm10;
}

QLineSeries* AirQualitySensor::getCo2Vals() const{
    return co2Vals;
}

QLineSeries* AirQualitySensor::getPm25Vals() const{
    return pm25Vals;
}

QLineSeries* AirQualitySensor::getPm10Vals() const{
    return pm10Vals;
}

void AirQualitySensor::setCo2(int c){
    co2=c;
}

void AirQualitySensor::setPm25(double p){
    pm25=p;
}

void AirQualitySensor::setPm10(double p){
    pm10=p;
}

void AirQualitySensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void AirQualitySensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}

void AirQualitySensor::onTimerTimeout(){
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();

    co2=genIntVal(300,950);
    pm25=genDoubleVal(35.0);
    pm10=genDoubleVal(50.0);

    co2Vals->append(currentTime, co2);
    if(co2Vals->count()>=20) co2Vals->remove(0);

    pm25Vals->append(currentTime, pm25);
    if(pm25Vals->count()>20) pm25Vals->remove(0);

    pm10Vals->append(currentTime, pm10);
    if(pm10Vals->count()>20) pm10Vals->remove(0);
}
