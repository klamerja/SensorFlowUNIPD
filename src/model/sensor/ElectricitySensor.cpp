#include "ElectricitySensor.h"

ElectricitySensor::ElectricitySensor(std::string name, QTimer* timer, int dist, std::string id) :
    AbstractSensor(name, timer, dist, id),
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

void ElectricitySensor::request(IConstSensorHandler* handler) const{
    handler->handle(this);
}

void ElectricitySensor::onTimerTimeout(){
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();
    watt=genDoubleVal(3000.0);
    voltage=genIntVal(220, 231);

    wattVals->append(currentTime, watt);
    if(wattVals->count()>20) wattVals->remove(0);

    voltageVals->append(currentTime, voltage);
    if(voltageVals->count()>20) voltageVals->remove(0);
}

