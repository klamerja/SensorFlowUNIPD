#include "Controller.h"
#include "model/json/JSONhandler.h"

#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

Controller::Controller(MainWindow* m) : mainWindow(m), jsonUtils(nullptr), sharedTimer(new QTimer){
    sharedTimer->start(2000);
}

void Controller::resetController(){
    filePath="";
    if(jsonUtils){
        delete jsonUtils;
        jsonUtils=nullptr;
    }
    sensors.clear();
}

void Controller::addSensor(const QString& name, int type, int distribution){
    AbstractSensor* sensor;
    switch(type){
        case sensorType::AirQuality:
            sensor=new AirQualitySensor(name.toStdString(), sharedTimer, distribution);
        break;
        case sensorType::Electricity:
            sensor=new ElectricitySensor(name.toStdString(), sharedTimer, distribution);
        break;
        case sensorType::Pressure:
            sensor=new PressureSensor(name.toStdString(), sharedTimer, distribution);
        break;
        case sensorType::TemperatureHumidity:
            sensor=new TempHumiditySensor(name.toStdString(), sharedTimer, distribution);
        break;
    }

    //Aggiornamento vettori
    sensors.push_back(sensor);
    mainWindow->repaintSensorsList(sensors);
}

void Controller::deleteSensor(AbstractSensor* sensor){
    auto it=sensors.begin();
    while(it!=sensors.end()){
        if((*it)->getId()==sensor->getId()){
            sensors.erase(it);
        }else{
            ++it;
        }
    }
}

bool Controller::isJsonInstanced() const{
    return jsonUtils!=nullptr;
}

QTimer* Controller::getTimer() const{
    return sharedTimer;
}

void Controller::searchWidgets(const QString& text) const{
    if(text.isEmpty()){
        mainWindow->repaintSensorsList(sensors);
    }else{
        QRegularExpression exp("^"+text);
        std::vector<AbstractSensor*> matches;
        for(AbstractSensor* sensor:sensors){
            QRegularExpressionMatch match=exp.match(QString::fromStdString(sensor->getName()));
            if(match.hasMatch())matches.push_back(sensor);
        }
        mainWindow->repaintSensorsList(matches);
    }
}

void Controller::refreshSensorsList(){
    mainWindow->repaintSensorsList(sensors);
}

//Slots
void Controller::newFile(){
    resetController();
    filePath=QFileDialog::getSaveFileName(mainWindow, ("Crea nuovo file"), QDir::homePath(), "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        delete jsonUtils;
        jsonUtils=new JSONhandler(filePath);
        sensors=jsonUtils->getSensors(sharedTimer); //Non serve
        mainWindow->repaintSensorsList(sensors);
    }
}

void Controller::openFile(){
    resetController();
    filePath=QFileDialog::getOpenFileName(mainWindow, ("Apri file"), QDir::homePath(),  "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        delete jsonUtils;
        jsonUtils=new JSONhandler(filePath);
        sensors=jsonUtils->getSensors(sharedTimer);
        mainWindow->repaintSensorsList(sensors);
    }
}

void Controller::saveFile(){
    if(jsonUtils)jsonUtils->updateJSON(sensors);
    else{
        QMessageBox warning;
        warning.setModal(true);
        warning.setText("File non aperto");
        warning.setIcon(QMessageBox::Critical);
        warning.addButton(QMessageBox::Ok);
        warning.exec();
    }
}
