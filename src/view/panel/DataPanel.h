#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include <QList>
#include <QChartView>
#include <QPushButton>
#include <QVBoxLayout>

#include "../../model/sensor/AbstractSensor.h"
#include "../../model/sensor/PressureSensor.h"
#include "../../model/sensor/TempHumiditySensor.h"
#include "../../model/sensor/ElectricitySensor.h"
#include "../../model/sensor/AirQualitySensor.h"
#include "../../model/sensor/IConstSensorHandler.h"

class DataPanel : public QWidget, public IConstSensorHandler{
private:
    QTimer* timer;
    QList<QChart*> charts;
    QVBoxLayout* lay;
public:
    DataPanel(AbstractSensor*,QTimer*);
    static QChartView* chartView();
    static QChart* chart();
    static QPushButton* leftBtn();
    static QPushButton* rightBtn();
    virtual void handle(const AirQualitySensor*) override;
    virtual void handle(const ElectricitySensor*) override;
    virtual void handle(const PressureSensor*) override;
    virtual void handle(const TempHumiditySensor*) override;
    ~DataPanel();
};

#endif // DATAPANEL_H

