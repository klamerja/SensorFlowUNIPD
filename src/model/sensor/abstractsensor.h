#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <string>

class AbstractSensor{
private:
    const std::string uid;
    std::string name;
protected:
    AbstractSensor(std::string);
public:
    virtual ~AbstractSensor()=0;
    std::string getUid() const;
    std::string getName() const;
    void setName(std::string n);
};

#endif // ABSTRACTSENSOR_H
