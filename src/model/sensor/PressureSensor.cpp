#include "PressureSensor.h"

PressureSensor::PressureSensor(std::string n, QTimer* t, std::string i) : AbstractSensor(n, t, i), pressure(0){}

double PressureSensor::getPressure() const{
    return pressure;
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
