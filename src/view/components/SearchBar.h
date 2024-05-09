#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QFrame>
#include <QLineEdit>

class SearchBar:public QFrame{
    Q_OBJECT
public:
    SearchBar();
signals:
    void textChanged(const QString& s);
};
#endif