#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensormenu/sensormenu.h"

class MainWindow : public QMainWindow{
private:
    QMenuBar* menuBar;
    SensorMenu* sensorMenu;
    void createMenu();
    void setupUI();
public:
    explicit MainWindow(QWidget* parent=0);
protected:

public slots:
    void newFile();
    void openFile();
    void saveFile();
};

#endif // MAINWINDOW_H
