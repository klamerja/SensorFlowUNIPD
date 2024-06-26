#include "AbstractSensor.h"
#include "view/MainWindow.h"

#include <QUuid>
#include <QRandomGenerator>
#include <random>

AbstractSensor::AbstractSensor(std::string n, QTimer* t, int dist, std::string i) :
    name(n),
    timer(t),
    id(i.empty() ? QUuid::createUuid().toString(QUuid::WithoutBraces).toStdString() : i),
    distribution(dist){
    connect(timer, &QTimer::timeout, this, &AbstractSensor::onTimerTimeout);
}

AbstractSensor::~AbstractSensor() =default;

int AbstractSensor::genIntVal(int min, int max){
    switch(distribution){
        case distributionType::Casual:{
            return QRandomGenerator::global()->bounded(min,max);
        }
        break;
        case distributionType::Gauss:{
            std::random_device rd;
            std::mt19937 gen(rd()); 
            std::normal_distribution<double> distribution((max+min)/2.0, (max-min)/10.0);
            int val;
            do{
                val=ceil(distribution(gen));
            }while(val<min & val>max);
            return val;
        }
        break;
        break;
        case distributionType::Uniform:{
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(min, max);
            return dist(gen);
        }
        break;
        default:
            qTerminate();
    }
}

double AbstractSensor::genDoubleVal(double max){
    switch(distribution){
        case distributionType::Casual:{
            return QRandomGenerator::global()->bounded(max);
        }
        break;
        case distributionType::Gauss:{
            std::random_device rd;
            std::mt19937 gen(rd()); 
            std::normal_distribution<double> distribution((max)/2, (max)/10.0);
            int val;
            do{
                val=distribution(gen);
            }while(val<0 & val>max);
            return val;
        }
        break;
        break;
        case distributionType::Uniform:{
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dist(0, max);
            return dist(gen);
        }
        break;
        default:
            qTerminate();
    }
}

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

int AbstractSensor::getDistribution() const{
    return distribution;
}

void AbstractSensor::setDistribution(int dist){
    distribution=dist;
}
