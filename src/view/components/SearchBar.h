#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include "view/MainWindow.h"
#include <QFrame>
#include <QLineEdit>

class SearchBar:public QFrame{
    Q_OBJECT
public:
    SearchBar(MainWindow* main);
signals:
    void textChanged(const QString& s);
private slots:
    void updateBackground();
};
#endif