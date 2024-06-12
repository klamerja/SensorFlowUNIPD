#include "ItemCard.h"
#include "view/MainWindow.h"

#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QSvgWidget>

ItemCard::ItemCard(AbstractSensor* s, MainWindow* main) : sensor(s), mainWindow(main), layout(new QHBoxLayout), labelsLayout(new QVBoxLayout), labels(new QWidget), name(new QLabel(QString::fromStdString(sensor->getName()))), deleteButton(new QPushButton){
    setStyleSheet("*{background-color: palette(base); border-radius: 12px;} ItemCard:hover{border: 2px solid #0ABAB5;} ItemCard:focus{border: 2px solid #0ABAB5;}");
    connect(main, &MainWindow::themeChanged, this, &ItemCard::updateBackground);
    setFixedSize(250,100);

    QIcon deleteIcon(":/assets/Delete.svg");
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(35,35);
    deleteButton->setFlat(true);
    deleteButton->setIconSize(QSize(20,20));

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

void ItemCard::updateBackground(){
    setStyleSheet("*{background-color: palette(base); border-radius: 12px;} ItemCard:hover{border: 2px solid #0ABAB5;} ItemCard:focus{border: 2px solid #0ABAB5;}");
}

ItemCard::~ItemCard(){
    delete layout;
}

