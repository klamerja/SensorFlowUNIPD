#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <string>
#include <QTimer>
#include <QRandomGenerator>
#include <QObject>
#include <QLineSeries>
#include <QSplineSeries>
#include <QDateTime>

#include "ISensorHandler.h"
#include "IConstSensorHandler.h"

class AbstractSensor : public QObject{
private:
    std::string name;
    QTimer* timer;
    std::string id;
protected:
    QRandomGenerator* randomGen;
    AbstractSensor(std::string, QTimer*, std::string i="");
public:
    virtual ~AbstractSensor() =0;
    std::string getName() const;
    void setName(std::string);
    std::string getId() const;
    void setId(std::string);
    virtual void request(ISensorHandler*) =0;
    virtual void request(IConstSensorHandler*) =0;
signals:
    void refreshVal();
private slots:
    void changeVal();
    virtual void onTimerTimeout()=0;
};

#endif // ABSTRACTSENSOR_H
