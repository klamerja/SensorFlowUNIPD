#include "PressureSensor.h"

PressureSensor::PressureSensor(std::string n, QTimer* t, std::string i) :
    AbstractSensor(n, t, i), pressure(0),
    pressureVals(new QSplineSeries) {}

double PressureSensor::getPressure() const{
    return pressure;
}

QSplineSeries* PressureSensor::getPressureVals() const{
    return pressureVals;
}

void PressureSensor::setPressure(double p){
    pressure=p;
}

void PressureSensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void PressureSensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}

void PressureSensor::onTimerTimeout(){
    pressure=randomGen->bounded(1094.0); //Misurata in hPa

    pressureVals->append(QDateTime::currentMSecsSinceEpoch(), pressure);
    if(pressureVals->count()>20) pressureVals->remove(0);
}
