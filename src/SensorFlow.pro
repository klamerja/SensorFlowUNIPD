TEMPLATE = app
TARGET = SensorFlow
INCLUDEPATH += .

QT += core widgets

# Input
SOURCES += main.cpp \
    model/sensor/abstractsensor.cpp \
    model/sensor/temphumiditysensor.cpp \
    view/mainwindow.cpp \
    view/sensormenu/sensormenu.cpp

HEADERS += \
    model/sensor/abstractsensor.h \
    model/sensor/temphumiditysensor.h \
    view/mainwindow.h \
    view/sensormenu/sensormenu.h

RESOURCES += \
    resources.qrc
