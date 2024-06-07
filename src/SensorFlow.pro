TEMPLATE = app
TARGET = SensorFlow
INCLUDEPATH += .

QT += core widgets charts svg svgwidgets gui

# Input
SOURCES += main.cpp \
    controller/Controller.cpp \
    model/json/JSONhandler.cpp \
    model/sensor/AbstractSensor.cpp \
    model/sensor/AirQualitySensor.cpp \
    model/sensor/ElectricitySensor.cpp \
    model/sensor/PressureSensor.cpp \
    model/sensor/TempHumiditySensor.cpp \
    view/MainWindow.cpp \
    view/panel/AddPanel.cpp \
    view/panel/DataPanel.cpp \
    view/panel/HomePanel.cpp \
    view/sensorMenu/ItemCard.cpp \
    view/sensorMenu/SensorMenu.cpp \
    view/components/SearchBar.cpp \
    view/components/AddButton.cpp

HEADERS += \
    controller/Controller.h \
    model/json/JSONhandler.h \
    model/sensor/AbstractSensor.h \
    model/sensor/AirQualitySensor.h \
    model/sensor/ElectricitySensor.h \
    model/sensor/IConstSensorHandler.h \
    model/sensor/ISensorHandler.h \
    model/sensor/PressureSensor.h \
    model/sensor/TempHumiditySensor.h \
    view/MainWindow.h \
    view/panel/AddPanel.h \
    view/panel/DataPanel.h \
    view/panel/HomePanel.h \
    view/sensorMenu/ItemCard.h \
    view/sensorMenu/SensorMenu.h \
    view/components/SearchBar.h \
    view/components/AddButton.h 

RESOURCES += \
    resources.qrc

DISTFILES += \
    assets/left.png \
    assets/logo.png \
    assets/right.png