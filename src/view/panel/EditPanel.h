#ifndef EDITPANEL_H
#define EDITPANEL_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "../MainWindow.h"
#include "../../controller/Controller.h"
#include "../../model/sensor/AbstractSensor.h"

class EditPanel : public QDialog{
    Q_OBJECT
private:
    MainWindow* app;
    AbstractSensor* sensor;
    QLineEdit* nameEdit;
    QComboBox* distributionSelection;
public:
    EditPanel(MainWindow*, AbstractSensor*);
public slots:
    void onReject();
    void onSubmit();
};

#endif // EDITPANEL_H