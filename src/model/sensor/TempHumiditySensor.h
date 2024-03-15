#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include "AbstractSensor.h"

class TempHumiditySensor : public AbstractSensor{
private:
    int temperature;
    int humidity;
    QSplineSeries* temperatureVals;
    QSplineSeries* humidityVals;
public:
    TempHumiditySensor(std::string, QTimer*, std::string="");
    ~TempHumiditySensor() =default;
    int getTemperature() const;
    int getHumidity() const;
    QSplineSeries* getTemperatureVals() const;
    QSplineSeries* getHumidityVals() const;
    void setTemperature(int);
    void setHumidity(int);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // TEMPHUMIDITYSENSOR_H
