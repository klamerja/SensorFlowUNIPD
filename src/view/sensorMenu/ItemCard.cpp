#include "ItemCard.h"
#include "view/MainWindow.h"
#include "view/panel/EditPanel.h"

#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QSvgWidget>

ItemCard::ItemCard(AbstractSensor* s, MainWindow* main) : sensor(s), mainWindow(main), layout(new QHBoxLayout), labelsLayout(new QVBoxLayout), labels(new QWidget), name(new QLabel(QString::fromStdString(sensor->getName()))){
    setStyleSheet("*{background-color: palette(base); border-radius: 12px;} ItemCard:hover{border: 2px solid #0ABAB5;} ItemCard:focus{border: 2px solid #0ABAB5;}");
    connect(main, &MainWindow::themeChanged, this, &ItemCard::updateBackground);
    setFixedSize(250,100);

    QIcon editIcon(":/assets/Edit.svg");
    QPushButton* editButton=new QPushButton;
    editButton->setIcon(editIcon);
    editButton->setFixedSize(35,35);
    editButton->setFlat(true);
    editButton->setIconSize(QSize(15,15));

    QIcon deleteIcon(":/assets/Delete.svg");
    QPushButton* deleteButton=new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(35,35);
    deleteButton->setFlat(true);
    deleteButton->setIconSize(QSize(20,20));

    setFocusPolicy(Qt::ClickFocus);

    connect(this, &ItemCard::itemClicked, mainWindow, &MainWindow::onItemClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ItemCard::deleteItem);
    connect(editButton, &QPushButton::clicked, this, &ItemCard::editItem);

    setLayout(layout);
    labels->setLayout(labelsLayout);

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);

    QFont nameFont(name->font());
    nameFont.setBold(true);
    name->setFont(nameFont);

    sensor->request(this);
}

void ItemCard::handle(const AirQualitySensor*){
    type=new QLabel("Qualità dell'aria");
    type->setStyleSheet("color: #6e6e6e");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();
}

void ItemCard::handle(const ElectricitySensor*){
    type=new QLabel("Elettricità");
    type->setStyleSheet("color: #6e6e6e");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();
}

void ItemCard::handle(const PressureSensor*){
    type=new QLabel("Pressione atmosferica");
    type->setStyleSheet("color: #6e6e6e");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();
}

void ItemCard::handle(const TempHumiditySensor*){
    QLabel* type=new QLabel("Temperatura e umidità");
    type->setStyleSheet("color: #6e6e6e");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();
}

void ItemCard::mousePressEvent(QMouseEvent*){
    emit itemClicked(this);
}

void ItemCard::focusOutEvent(QFocusEvent *event){
    mainWindow->removeFocusedItem();
    QFrame::focusOutEvent(event);
}

AbstractSensor* ItemCard::getSensor() const{
    return sensor;
}

void ItemCard::deleteItem(){
    mainWindow->deleteSensor(this);
}

void ItemCard::editItem(){
    mainWindow->setHomePanel();
    EditPanel editPanel(mainWindow, sensor);
    editPanel.exec();
}

void ItemCard::updateBackground(){
    setStyleSheet("*{background-color: palette(base); border-radius: 12px;} ItemCard:hover{border: 2px solid #0ABAB5;} ItemCard:focus{border: 2px solid #0ABAB5;}");
}

ItemCard::~ItemCard(){
    delete layout;
}

