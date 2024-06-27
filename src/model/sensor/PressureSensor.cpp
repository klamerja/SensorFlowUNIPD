#include "PressureSensor.h"

PressureSensor::PressureSensor(std::string name, QTimer* timer, int dist, std::string id) :
    AbstractSensor(name, timer, dist, id), pressure(0),
    pressureVals(new QLineSeries) {}

double PressureSensor::getPressure() const{
    return pressure;
}

QLineSeries* PressureSensor::getPressureVals() const{
    return pressureVals;
}

void PressureSensor::setPressure(double p){
    pressure=p;
}

void PressureSensor::request(ISensorHandler* handler){
    handler->handle(this);
}

void PressureSensor::request(IConstSensorHandler* handler) const{
    handler->handle(this);
}

void PressureSensor::onTimerTimeout(){
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();
    pressure=genDoubleVal(1094);

    pressureVals->append(currentTime, pressure);
    if(pressureVals->count()>20) pressureVals->remove(0);
}
