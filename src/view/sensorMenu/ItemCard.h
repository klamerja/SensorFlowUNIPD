#ifndef ITEMCARD_H
#define ITEMCARD_H

#include <QFrame>
#include <string>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "../MainWindow.h"
#include "../../model/sensor/AbstractSensor.h"
#include "../../model/sensor/TempHumiditySensor.h"
#include "../../model/sensor/PressureSensor.h"
#include "../../model/sensor/ElectricitySensor.h"
#include "../../model/sensor/AirQualitySensor.h"
#include "../../model/sensor/IConstSensorHandler.h"

class MainWindow;

class ItemCard : public QFrame, public IConstSensorHandler{
    Q_OBJECT
private:
    AbstractSensor* sensor;
    MainWindow* mainWindow;
    QHBoxLayout* layout;
    QVBoxLayout* labelsLayout;
    QWidget* labels;
    QLabel* name;
    QLabel* type;
    QPushButton* deleteButton;
public:
    ItemCard(AbstractSensor*, MainWindow*);
    void handle(const AirQualitySensor*) override;
    void handle(const ElectricitySensor*) override;
    void handle(const PressureSensor*) override;
    void handle(const TempHumiditySensor*) override;
    void mousePressEvent(QMouseEvent*) override;
    void focusOutEvent(QFocusEvent *event) override;
    AbstractSensor* getSensor() const;
    ~ItemCard();
signals:
    void itemClicked(ItemCard*);
public slots:
    void deleteItem();
private slots:
    void updateBackground();
};

#endif // ITEMCARD_H
