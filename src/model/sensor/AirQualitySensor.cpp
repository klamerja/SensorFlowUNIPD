#include "AirQualitySensor.h"

#include <QList>

AirQualitySensor::AirQualitySensor(std::string n, QTimer* t, std::string i) :
    AbstractSensor(n, t, i),
    co2(0),
    pm25(0),
    pm10(0),
    co2Vals(new QAreaSeries(new QLineSeries, new QLineSeries)),
    pm25Vals(new QAreaSeries(new QLineSeries, new QLineSeries)),
    pm10Vals(new QAreaSeries(new QLineSeries, new QLineSeries)) {}

int AirQualitySensor::getCo2() const{
    return co2;
}

double AirQualitySensor::getPm25() const{
    return pm25;
}

double AirQualitySensor::getPm10() const{
    return pm10;
}

QAreaSeries* AirQualitySensor::getCo2Vals() const{
    return co2Vals;
}

QAreaSeries* AirQualitySensor::getPm25Vals() const{
    return pm25Vals;
}

QAreaSeries* AirQualitySensor::getPm10Vals() const{
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

    co2=randomGen->bounded(300,950); //ppm di co2
    pm25=randomGen->bounded(35.0); //microgrammi per mc
    pm10=randomGen->bounded(50.0); //microgrammi per mc

    //Lower series settings
    co2Vals->lowerSeries()->append(currentTime, 0);
    pm25Vals->lowerSeries()->append(currentTime, 0);
    pm10Vals->lowerSeries()->append(currentTime, 0);

    co2Vals->upperSeries()->append(currentTime, co2);
    if(co2Vals->upperSeries()->count()>20) co2Vals->upperSeries()->remove(0);

    pm25Vals->upperSeries()->append(currentTime, pm25);
    if(pm25Vals->upperSeries()->count()>20) pm25Vals->upperSeries()->remove(0);

    pm10Vals->upperSeries()->append(currentTime, pm10);
    if(pm10Vals->upperSeries()->count()>20) pm10Vals->upperSeries()->remove(0);
}
