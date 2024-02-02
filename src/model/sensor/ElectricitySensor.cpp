#include "ElectricitySensor.h"

ElectricitySensor::ElectricitySensor(std::string n, QTimer* t, std::string i) : AbstractSensor(n, t, i), watt(0), voltage(0) {}

double ElectricitySensor::getWatt() const{
    return watt;
}

double ElectricitySensor::getVoltage() const{
    return voltage;
}

void ElectricitySensor::setWatt(double w){
    watt=w;
}

void ElectricitySensor::setVoltage(double v){
    voltage=v;
}

void ElectricitySensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void ElectricitySensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}


