#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <vector>

#include "../model/sensor/AbstractSensor.h"
#include "../model/json/JSONhandler.h"
#include "../view/MainWindow.h"

class MainWindow; //Forward declaration per dipendenza circolare

class Controller : public QObject{
private:
    MainWindow* mainWindow;
    QString filePath;
    JSONhandler* jsonUtils;
    std::vector<AbstractSensor*> sensors;
    bool changed;
    std::vector<AbstractSensor*> notSaved;
    QTimer* sharedTimer;
public:
    Controller(MainWindow*);
public slots:
    void newFile();
    void openFile();
    void saveFile();
    void newSensor();
    void deleteSensor();
};

#endif // CONTROLLER_H
