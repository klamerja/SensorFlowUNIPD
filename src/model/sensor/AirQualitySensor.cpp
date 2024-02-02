#include "AirQualitySensor.h"

AirQualitySensor::AirQualitySensor(std::string n, QTimer* t, std::string i) : AbstractSensor(n, t, i), co2(0), pm25(0), pm10(0) {}

unsigned int AirQualitySensor::getCo2() const{
    return co2;
}
double AirQualitySensor::getPm25() const{
    return pm25;
}
double AirQualitySensor::getPm10() const{
    return pm10;
}
void AirQualitySensor::setCo2(unsigned int c){
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
