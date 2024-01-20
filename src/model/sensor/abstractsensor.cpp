#include "abstractsensor.h"

#include <QUuid>

AbstractSensor::AbstractSensor(std::string n) : uid(QUuid::createUuid().toString().toStdString()), name(n){}

AbstractSensor::~AbstractSensor() {}

std::string AbstractSensor::getUid() const{
    return uid;
}
std::string AbstractSensor::getName() const{
    return name;
}

void AbstractSensor::setName(std::string n){
    name=n;
}


