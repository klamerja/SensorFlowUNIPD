#include "Controller.h"

#include <QFileDialog>
#include <QDebug>


Controller::Controller(MainWindow* m) : mainWindow(m),changed(false){}

//Slots
void Controller::newFile(){
    filePath=QFileDialog::getSaveFileName(mainWindow, ("Crea nuovo file"), QDir::homePath(), "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        if(jsonUtils==nullptr){
            jsonUtils=new JSONhandler(filePath);
        }
    }
}

void Controller::openFile(){
    filePath=QFileDialog::getOpenFileName(mainWindow, ("Apri file"), QDir::homePath(),  "JSON Files (*.json)");
    if(!filePath.isEmpty()){
        if(jsonUtils==nullptr){
            jsonUtils=new JSONhandler(filePath);
        }
    }
}

void Controller::saveFile(){
    //TODO
}

void Controller::newSensor(){
    //TODO
}

void Controller::deleteSensor(){
    //TODO
}


