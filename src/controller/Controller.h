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
    QTimer* sharedTimer;
    void resetController();
public:
    Controller(MainWindow*);
    void addSensor(const QString&,int,int);
    void deleteSensor(AbstractSensor*);
    bool isJsonInstanced() const;
    QTimer* getTimer() const;
    void searchWidgets(const QString&) const;
    void refreshSensorsList();
public slots:
    void newFile();
    void openFile();
    void saveFile();
};

#endif // CONTROLLER_H
