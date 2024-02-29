#include "Controller.h"

#include <QFileDialog>
#include <QDebug>
#include <string>

Controller::Controller(MainWindow* m) : mainWindow(m),changed(false), sharedTimer(new QTimer){
    sharedTimer->start(2000);
}

void Controller::resetController(){
    filePath="";
    if(jsonUtils)delete jsonUtils;
    sensors.clear();
    toBeRemoved.clear();
    changed=false;
}

void Controller::addSensor(const QString& name, int type){
    AbstractSensor* sensor;
    switch(type){
        case sensorType::AirQuality:
            sensor=new AirQualitySensor(name.toStdString(), sharedTimer);
        break;
        case sensorType::Electricity:
            sensor=new ElectricitySensor(name.toStdString(), sharedTimer);
        break;
        case sensorType::Pressure:
            sensor=new PressureSensor(name.toStdString(), sharedTimer);
        break;
        case sensorType::TemperatureHumidity:
            sensor=new TempHumiditySensor(name.toStdString(), sharedTimer);
        break;
    }

    //Aggiornamento vettori
    changed=true;
    sensors.push_back(sensor);
    notSaved.push_back(sensor);

    mainWindow->repaintSensorsList(sensors);
}

void Controller::deleteSensor(AbstractSensor* sensor){
    auto it=sensors.begin();
    while(it!=sensors.end()){
        if((*it)->getId()==sensor->getId()){
            changed=true;
            toBeRemoved.push_back((*it));
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
        std::vector<AbstractSensor*> matches;
        for(AbstractSensor* sensor:sensors){
            if(QString::fromStdString(sensor->getName()).contains(text, Qt::CaseInsensitive))
                matches.push_back(sensor);
        }
        mainWindow->repaintSensorsList(matches);
    }
}

//Slots
void Controller::newFile(){
    resetController();
    filePath=QFileDialog::getSaveFileName(mainWindow, ("Crea nuovo file"), QDir::homePath(), "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        if(jsonUtils==nullptr){
            jsonUtils=new JSONhandler(filePath);
        }
    }
}

void Controller::openFile(){
    resetController();
    filePath=QFileDialog::getOpenFileName(mainWindow, ("Apri file"), QDir::homePath(),  "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        if(jsonUtils==nullptr){
            jsonUtils=new JSONhandler(filePath);
        }
    }
}

void Controller::saveFile(){
    if(changed){
        //Rimozione dal JSON dei sensori eliminati
        jsonUtils->removeSensors(toBeRemoved);
        //Salvataggio sensori nuovi
        jsonUtils->addNewSensors(notSaved);
        changed=false;
    }
}


