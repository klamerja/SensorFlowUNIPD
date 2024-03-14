#ifndef AIRQUALITYSENSOR_H
#define AIRQUALITYSENSOR_H

#include "AbstractSensor.h"

class AirQualitySensor : public AbstractSensor{
private:
    int co2;
    double pm25;
    double pm10;
    QAreaSeries* co2Vals;
    QAreaSeries* pm25Vals;
    QAreaSeries* pm10Vals;
public:
    AirQualitySensor(std::string, QTimer*, std::string="");
    ~AirQualitySensor() =default;
    int getCo2() const;
    double getPm25() const;
    double getPm10() const;
    QAreaSeries* getCo2Vals() const;
    QAreaSeries* getPm25Vals() const;
    QAreaSeries* getPm10Vals() const;
    void setCo2(int);
    void setPm25(double);
    void setPm10(double);
    void request(ISensorHandler*) override;
    void request(IConstSensorHandler*) override;
public slots:
    void onTimerTimeout() override;
};

#endif // AIRQUALITYSENSOR_H
