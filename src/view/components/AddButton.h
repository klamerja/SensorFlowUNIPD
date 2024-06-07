#ifndef ADDBUTTON_H
#define ADDBUTTON_H

#include <QSvgWidget>
#include <QPushButton>

class AddButton : public QSvgWidget{
    Q_OBJECT
public:
    AddButton();
private:
    void mousePressEvent(QMouseEvent*) override;
signals:
    void clicked();
};

#endif // ADDBUTTON_H