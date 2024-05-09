#include <QApplication>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QFontDatabase>
#include <QFont>

#include "view/MainWindow.h"
#include "model/sensor/AbstractSensor.h"
#include "model/sensor/AirQualitySensor.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QFile stylesheet(":/assets/stylesheet.qss");
    stylesheet.open(QFile::ReadOnly);
    app.setStyleSheet(stylesheet.readAll());

    QIcon icon(":/assets/IconApp.png");
    app.setWindowIcon(icon);
    
    MainWindow window;
    window.setWindowTitle("SensorFlow");
    window.showNormal();
    
    return app.exec();
}
