#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "../MainWindow.h"

class AddPanel : public QDialog{
private:
    MainWindow* app;
    QLineEdit* nameEdit;
    QComboBox* typeSelection;
public:
    AddPanel(MainWindow*);
public slots:
    void onReject();
    void onSubmit();
};

#endif // ADDPANEL_H
