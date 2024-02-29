#include "JSONhandler.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValueRef>

#include "../sensor/AirQualitySensor.h"
#include "../sensor/ElectricitySensor.h"
#include "../sensor/PressureSensor.h"
#include "../sensor/TempHumiditySensor.h"

JSONhandler::JSONhandler(QString p) : path(p){
    QFile jsonFile(path);
    jsonFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content=jsonFile.readAll();
    if(!content.isEmpty()){
        document=new QJsonDocument(QJsonDocument::fromJson(content.toUtf8()));
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
    if(!val.isNull() && val.isArray()){ //Controllo array da testare se necessario
        QJsonArray sensorsArray(val.toArray());
        for(auto it=sensorsArray.begin();it!=sensorsArray.end();it++){
            if((*it).isObject()){
                QJsonObject sensor((*it).toObject());
                if(sensor["type"].toString()=="temp"){
                    sensors.push_back(new TempHumiditySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["id"].toString().toStdString()));
                }else if(sensor["type"].toString()=="air"){
                    sensors.push_back(new AirQualitySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["id"].toString().toStdString()));
                }else if(sensor["type"].toString()=="power"){
                    sensors.push_back(new ElectricitySensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["id"].toString().toStdString()));
                }else if(sensor["type"].toString()=="press"){
                    sensors.push_back(new PressureSensor(sensor["name"].toString().toStdString(), sharedTimer, sensor["id"].toString().toStdString()));
                }
            }
        }
    }
    return sensors;
}

void JSONhandler::addNewSensors(std::vector<AbstractSensor*>& diffs){
    for(auto it=diffs.begin(); it!=diffs.end();it++){
        (*it)->request(this);
    }
    QFile jsonFile(path);
    if(!jsonFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        qTerminate();
    }
    jsonFile.seek(0);
    jsonFile.write(document->toJson());
    qWarning()<<document->toJson();
    jsonFile.close();
}

void JSONhandler::removeSensors(std::vector<AbstractSensor*>& diffs){
    QJsonObject obj=document->object();
    QJsonValue val=obj["sensors"];
    if(!val.isNull() && val.isArray()){ //Controllo array da testare se necessario
        QJsonArray sensorsArray(val.toArray());

        for(auto it=diffs.begin(); it!=diffs.end();it++){
            for(int j=0;j<sensorsArray.size();it++){
                QJsonObject sensor(sensorsArray[j].toObject());
                if(sensor["id"].toString().toStdString()==(*it)->getId()){
                    sensorsArray.removeAt(j);
                }
            }
        }
    }
    QFile jsonFile(path);
    if(!jsonFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        qTerminate();
    }
    jsonFile.seek(0);
    jsonFile.write(document->toJson());
    jsonFile.close();
}

void JSONhandler::handle(const AirQualitySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]="air";
    if(document->object()["sensors"].isNull())qWarning()<<"Non nullo";
    if(document->object()["sensors"].isArray())qWarning()<<"È array";
    qWarning()<<sensorToJson;
    document->object()["sensors"].toArray().append(sensorToJson);
    qWarning()<<document->toJson();
}

void JSONhandler::handle(const ElectricitySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]="power";
    document->object()["sensors"].toArray().append(sensorToJson);
}

void JSONhandler::handle(const PressureSensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]="press";
    document->object()["sensors"].toArray().append(sensorToJson);
}

void JSONhandler::handle(const TempHumiditySensor* sensor){
    QJsonObject sensorToJson;
    sensorToJson["id"]=QString::fromStdString(sensor->getId());
    sensorToJson["name"]=QString::fromStdString(sensor->getName());
    sensorToJson["type"]="temp";
    document->object()["sensors"].toArray().append(sensorToJson);
}
