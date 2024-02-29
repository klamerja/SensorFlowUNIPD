#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include <QLabel>

class HomePanel : public QWidget{
private:
    QLabel* logoLabel;
public:
    HomePanel();
    ~HomePanel();
};

#endif // HOMEPANEL_H
