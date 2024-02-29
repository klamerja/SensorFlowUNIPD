#include "ItemCard.h"

#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QApplication>

ItemCard::ItemCard(AbstractSensor* s, MainWindow* main) : sensor(s), mainWindow(main), layout(new QHBoxLayout), labelsLayout(new QVBoxLayout), labels(new QWidget), name(new QLabel(QString::fromStdString(sensor->getName()))), deleteButton(new QPushButton){
    setObjectName("card");
    setFixedSize(250,100);

    QPixmap deleteIcon(":/assets/Delete.svg");
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(35,35);
    deleteButton->setFlat(true);
    deleteButton->setIconSize(QSize(18,18));

    connect(this, &ItemCard::itemClicked, mainWindow, &MainWindow::onItemClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ItemCard::deleteItem);

    setLayout(layout);
    labels->setLayout(labelsLayout);

    sensor->request(this);
}

void ItemCard::handle(const AirQualitySensor*){
    type=new QLabel("Qualità dell'aria");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const ElectricitySensor*){
    type=new QLabel("Elettricità");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const PressureSensor*){
    type=new QLabel("Pressione atmosferica");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const TempHumiditySensor*){
    QLabel* type=new QLabel("Temperatura e umidità");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

ItemCard::~ItemCard(){
    delete layout;
}

void ItemCard::mousePressEvent(QMouseEvent*){
    emit itemClicked(this);
}

void ItemCard::focusOutEvent(QFocusEvent *event){
    mainWindow->removeFocusedItem();
    mainWindow->setHomePanel();
    QFrame::focusOutEvent(event);
}

AbstractSensor* ItemCard::getSensor() const{
    return sensor;
}

void ItemCard::deleteItem(){
    mainWindow->deleteSensor(this);
}

