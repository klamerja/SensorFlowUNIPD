#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <string>
#include <QTimer>
#include <QRandomGenerator>
#include <QObject>
#include <QLineSeries>
#include <QDateTime>

#include "ISensorHandler.h"
#include "IConstSensorHandler.h"

class AbstractSensor : public QObject{
private:
    std::string name;
    QTimer* timer;
    std::string id;
    int distribution;
protected:
    AbstractSensor(std::string, QTimer*, int, std::string="");
    int genIntVal(int min, int max);
    double genDoubleVal(double max);
public:
    virtual ~AbstractSensor() =0;
    std::string getName() const;
    void setName(std::string);
    std::string getId() const;
    void setId(std::string);
    int getDistribution() const;
    void setDistribution(int);
    virtual void request(ISensorHandler*) =0;
    virtual void request(IConstSensorHandler*) const =0;
private slots:
    virtual void onTimerTimeout()=0;
};

#endif // ABSTRACTSENSOR_H
