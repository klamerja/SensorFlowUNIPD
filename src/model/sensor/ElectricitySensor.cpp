#include "ElectricitySensor.h"

ElectricitySensor::ElectricitySensor(std::string n, QTimer* t, std::string i) :
    AbstractSensor(n, t, i),
    watt(0),
    voltage(0),
    wattVals(new QLineSeries),
    voltageVals(new QLineSeries) {}

double ElectricitySensor::getWatt() const{
    return watt;
}

int ElectricitySensor::getVoltage() const{
    return voltage;
}

QLineSeries* ElectricitySensor::getWattVals() const{
    return wattVals;
}

QLineSeries* ElectricitySensor::getVoltageVals() const{
    return voltageVals;
}

void ElectricitySensor::setWatt(double w){
    watt=w;
}

void ElectricitySensor::setVoltage(int v){
    voltage=v;
}

void ElectricitySensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void ElectricitySensor::request(IConstSensorHandler* handler){
    handler->handle(this);
}

void ElectricitySensor::onTimerTimeout(){
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();
    watt=randomGen->bounded(3000.0); //Consumi in kWh
    voltage=randomGen->bounded(220,231);

    wattVals->append(currentTime, watt);
    if(wattVals->count()>20) wattVals->remove(0);

    voltageVals->append(currentTime, watt);
    if(voltageVals->count()>20) voltageVals->remove(0);
}

