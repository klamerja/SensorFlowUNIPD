#include "JSONhandler.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValueRef>
#include <cstdlib>

#include "../sensor/AirQualitySensor.h"
#include "../sensor/ElectricitySensor.h"
#include "../sensor/PressureSensor.h"
#include "../sensor/TempHumiditySensor.h"
#include "../../controller/Controller.h"

JSONhandler::JSONhandler(QString p) : path(p){
    QFile jsonFile(path);
    if(!jsonFile.open(QIODevice::ReadWrite))qTerminate();
    QByteArray content=jsonFile.readAll();
    if(!content.isEmpty()){
        document=new QJsonDocument(QJsonDocument::fromJson(content));
    }else{
        QJsonArray jsonArray;
        QJsonObject jsonObject;
        jsonObject["sensors"]=jsonArray;
        document=new QJsonDocument(jsonObject);
        jsonFile.write(document->toJson());
    }
    jsonFile.close();
}

std::vector<AbstractSensor*> JSONhandler::getSensors(QTimer* sharedTimer) const{
    std::vector<AbstractSensor*> sensors;
    QJsonObject obj=document->object();
    QJsonValue val=obj["sensors"];
    if(!val.isNull() && val.isArray()){
        QJsonArray sensorsArray(val.toArray());
        for(auto it=sensorsArray.begin();it!=sensorsArray.end();it++){
            if((*it).isObject()){
                QJsonObject sensor((*it).toObject());
                switch(sensor["type"].toInt()){
                    case sensorType::TemperatureHumidity:
                        sensors.push_back(new TempHumiditySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["distibution"].toInt(), sensor["id"].toString().toStdString()));
                    break;
                    case sensorType::AirQuality:
                        sensors.push_back(new AirQualitySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["distibution"].toInt(), sensor["id"].toString().toStdString()));
                    break;
                    case sensorType::Electricity:
                        sensors.push_back(new ElectricitySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["distibution"].toInt(), sensor["id"].toString().toStdString()));
                    break;
                    case sensorType::Pressure:
                        sensors.push_back(new PressureSensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["distibution"].toInt(), sensor["id"].toString().toStdString()));
                    break;
                    default:
                        qTerminate();
                }
            }
        }
    }
    return sensors;
}

void JSONhandler::updateJSON(std::vector<AbstractSensor*>& sensors){
    QJsonObject obj;
    QJsonArray arr;
    obj["sensors"]=arr;
    document->setObject(obj);
    for(auto it=sensors.begin(); it!=sensors.end();it++){
        (*it)->request(this);
    }
    QFile jsonFile(path);
    if(!jsonFile.open(QIODevice::WriteOnly))qTerminate();
    jsonFile.write(document->toJson());
}

void JSONhandler::handle(const AirQualitySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]=sensorType::AirQuality;
    sensorToJson["distribution"]=sensor->getDistribution();

    QJsonObject obj(document->object());
    QJsonArray arr(obj["sensors"].toArray());
    arr.append(sensorToJson);
    obj["sensors"]=arr;
    document->setObject(obj);
}

void JSONhandler::handle(const ElectricitySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]=sensorType::Electricity;
    sensorToJson["distribution"]=sensor->getDistribution();

    QJsonObject obj(document->object());
    QJsonArray arr(obj["sensors"].toArray());
    arr.append(sensorToJson);
    obj["sensors"]=arr;
    document->setObject(obj);
}

void JSONhandler::handle(const PressureSensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]=sensorType::Pressure;
    sensorToJson["distribution"]=sensor->getDistribution();

    QJsonObject obj(document->object());
    QJsonArray arr(obj["sensors"].toArray());
    arr.append(sensorToJson);
    obj["sensors"]=arr;
    document->setObject(obj);
}

void JSONhandler::handle(const TempHumiditySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]=sensorType::TemperatureHumidity;
    sensorToJson["distribution"]=sensor->getDistribution();

    QJsonObject obj(document->object());
    QJsonArray arr(obj["sensors"].toArray());
    arr.append(sensorToJson);
    obj["sensors"]=arr;
    document->setObject(obj);
}
