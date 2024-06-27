#include "AddButton.h"

AddButton::AddButton() : QSvgWidget(":/assets/AddButton.svg"){
    setObjectName("addButton");
    setFixedSize(50,50);
}


void AddButton::mousePressEvent(QMouseEvent*) {
    emit clicked();
}