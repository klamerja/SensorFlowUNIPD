#ifndef ICONSTSENSORHANDLER_H
#define ICONSTSENSORHANDLER_H

class AirQualitySensor;
class ElectricitySensor;
class PressureSensor;
class TempHumiditySensor;

class IConstSensorHandler{
public:
    virtual void handle(const AirQualitySensor*) =0;
    virtual void handle(const ElectricitySensor*) =0;
    virtual void handle(const PressureSensor*) =0;
    virtual void handle(const TempHumiditySensor*) =0;
};


#endif // ICONSTSENSORHANDLER_H
