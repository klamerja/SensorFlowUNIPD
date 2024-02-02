#ifndef ISENSORHANDLER_H
#define ISENSORHANDLER_H

class AirQualitySensor;
class ElectricitySensor;
class PressureSensor;
class TempHumiditySensor;

class ISensorHandler{
public:
    virtual void handle(AirQualitySensor*) =0;
    virtual void handle(ElectricitySensor*) =0;
    virtual void handle(PressureSensor*) =0;
    virtual void handle(TempHumiditySensor*) =0;
};

#endif // ISENSORHANDLER_H
