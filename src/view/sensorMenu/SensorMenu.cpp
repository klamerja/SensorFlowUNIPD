#include "SensorMenu.h"
#include "ItemCard.h"
#include "../components/SearchBar.h"
#include "../components/AddButton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineEdit>

SensorMenu::SensorMenu(MainWindow* main) : app(main), sensorsContainer(new QWidget){
    setFixedWidth(340);

    setStyleSheet("background-color: palette(window)");
    connect(main, &MainWindow::themeChanged, this, &SensorMenu::updateBackground);

    QVBoxLayout* menuLayout=new QVBoxLayout;
    menuLayout->setAlignment(Qt::AlignTop);
    setLayout(menuLayout);

    SearchBar* searchBar=new SearchBar(main);
    menuLayout->addWidget(searchBar);
    connect(searchBar, &SearchBar::textChanged, app, &MainWindow::searchWidgets);

    QScrollArea* scrollableArea=new QScrollArea;
    scrollableArea->setFrameShape(QFrame::NoFrame);
    menuLayout->addWidget(scrollableArea);
    scrollableArea->setWidgetResizable(true); //Altrimenti, lo scroll si adatta ai widget, e quindi non funziona
    scrollableArea->setWidget(sensorsContainer);

    AddButton* addButton=new AddButton;
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignLeft);
    menuLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(addButton);
    connect(addButton, &AddButton::clicked, app, &MainWindow::newSensor);
}

void SensorMenu::paintSensors(std::vector<AbstractSensor *> sensors){
    if(sensorsContainer->layout()!=nullptr){
        QLayoutItem* item;
        while((item=sensorsContainer->layout()->takeAt(0))!=nullptr){
            delete item->widget();
            delete item;
        }
        delete sensorsContainer->layout();
    }

    QVBoxLayout* layout=new QVBoxLayout;
    sensorsContainer->setLayout(layout);

    for(auto it=sensors.begin();it!=sensors.end();++it){
        layout->addWidget(new ItemCard(*it, app));
    }

    layout->addStretch();
}

void SensorMenu::updateBackground(){
    setStyleSheet("background-color: palette(window)");
}