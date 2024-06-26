#ifndef AIRQUALITYSENSOR_H
#define AIRQUALITYSENSOR_H

#include "AbstractSensor.h"

class AirQualitySensor : public AbstractSensor{
private:
    int co2;
    double pm25;
    double pm10;
    QLineSeries* co2Vals;
    QLineSeries* pm25Vals;
    QLineSeries* pm10Vals;
public:
    AirQualitySensor(std::string, QTimer*, int, std::string="");
    ~AirQualitySensor() =default;
    int getCo2() const;
    double getPm25() const;
    double getPm10() const;
    QLineSeries* getCo2Vals() const;
    QLineSeries* getPm25Vals() const;
    QLineSeries* getPm10Vals() const;
    void setCo2(int);
    void setPm25(double);
    void setPm10(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // AIRQUALITYSENSOR_H
