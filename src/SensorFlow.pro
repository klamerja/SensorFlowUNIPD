TEMPLATE = app
TARGET = SensorFlow
INCLUDEPATH += .

QT += core widgets

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
    view/sensorMenu/ItemCard.cpp \
    view/sensorMenu/SensorMenu.cpp

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
    view/sensorMenu/ItemCard.h \
    view/sensorMenu/SensorMenu.h

RESOURCES += \
    resources.qrc
