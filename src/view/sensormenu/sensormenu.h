#ifndef SENSORMENU_H
#define SENSORMENU_H

#include <QDockWidget>
#include "../MainWindow.h"

class MainWindow;

class SensorMenu : public QDockWidget{
private:
    MainWindow* app;
public:
    SensorMenu(MainWindow*);
};

#endif // SENSORMENU_H
