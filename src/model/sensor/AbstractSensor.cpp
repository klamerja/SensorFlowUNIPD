#include "AbstractSensor.h"

#include <QUuid>

AbstractSensor::AbstractSensor(std::string n, QTimer* t, std::string i) : name(n), timer(t), id(i==""? QUuid::createUuid().toString().toStdString() : i) {}

AbstractSensor::~AbstractSensor() =default;

std::string AbstractSensor::getName() const{
    return name;
}

void AbstractSensor::setName(std::string n){
    name=n;
}

std::string AbstractSensor::getId() const{
    return id;
}

void AbstractSensor::setId(std::string i){
    id=i;
}
