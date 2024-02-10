#include "ItemCard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

ItemCard::ItemCard(AbstractSensor* s, MainWindow* main) : sensor(s), app(main){
    connect(this, &ItemCard::itemClicked, app, &MainWindow::onItemClicked);
    setObjectName("card");
    setFixedSize(250,100);

    sensor->request(this);
}

void ItemCard::handle(const AirQualitySensor* sensor){

    QHBoxLayout* layout=new QHBoxLayout;
    setLayout(layout);

    QVBoxLayout* labelsLayout=new QVBoxLayout;
    QWidget* labels=new QWidget;
    labels->setLayout(labelsLayout);
    QLabel* name=new QLabel(QString::fromStdString(sensor->getName()));
    QLabel* type=new QLabel("Qualità dell'aria");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    QPixmap deleteIcon(":/assets/Delete(SVGRepo).svg");
    QPushButton* deleteButton= new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(50,50);
    deleteButton->setFlat(true);
    deleteButton->setIconSize(QSize(35,35));

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const ElectricitySensor* sensor){
    QHBoxLayout* layout=new QHBoxLayout;
    setLayout(layout);

    QVBoxLayout* labelsLayout=new QVBoxLayout;
    QWidget* labels=new QWidget;
    labels->setLayout(labelsLayout);
    QLabel* name=new QLabel(QString::fromStdString(sensor->getName()));
    QLabel* type=new QLabel("Corrente");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    QPixmap deleteIcon(":/assets/Delete(SVGRepo).svg");
    QPushButton* deleteButton= new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(50,50);

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const PressureSensor* sensor){
    QHBoxLayout* layout=new QHBoxLayout;
    setLayout(layout);

    QVBoxLayout* labelsLayout=new QVBoxLayout;
    QWidget* labels=new QWidget;
    labels->setLayout(labelsLayout);
    QLabel* name=new QLabel(QString::fromStdString(sensor->getName()));
    QLabel* type=new QLabel("Pressione atmosferica");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    QPixmap deleteIcon(":/assets/Delete(SVGRepo).svg");
    QPushButton* deleteButton= new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(50,50);

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::handle(const TempHumiditySensor* sensor){
    QHBoxLayout* layout=new QHBoxLayout;
    setLayout(layout);

    QVBoxLayout* labelsLayout=new QVBoxLayout;
    QWidget* labels=new QWidget;
    labels->setLayout(labelsLayout);
    QLabel* name=new QLabel(QString::fromStdString(sensor->getName()));
    QLabel* type=new QLabel("Temperatura e umidità");
    labelsLayout->addWidget(name);
    labelsLayout->addWidget(type);
    labelsLayout->addStretch();

    QPixmap deleteIcon(":/assets/Delete(SVGRepo).svg");
    QPushButton* deleteButton= new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setFixedSize(50,50);

    layout->addWidget(labels);
    layout->addStretch();
    layout->addWidget(deleteButton);
}

void ItemCard::mousePressEvent(QMouseEvent* event){
    emit itemClicked(this);
}
