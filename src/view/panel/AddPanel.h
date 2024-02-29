#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "../MainWindow.h"

class AddPanel : public QWidget{
private:
    MainWindow* app;
    QLineEdit* nameEdit;
    QComboBox* typeSelection;
public:
    AddPanel(MainWindow*);
public slots:
    void submit();
};

#endif // ADDPANEL_H
