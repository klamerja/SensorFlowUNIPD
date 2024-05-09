#include "SensorMenu.h"
#include "ItemCard.h"
#include "../components/SearchBar.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineEdit>

SensorMenu::SensorMenu(MainWindow* main) : app(main), sensorsContainer(new QWidget){
    setFixedWidth(300);
    //Layout del pannello sensori
    QVBoxLayout* menuLayout=new QVBoxLayout;
    menuLayout->setAlignment(Qt::AlignTop);
    setLayout(menuLayout);

    //Creazione search bar
    SearchBar* searchBar=new SearchBar;
    searchBar->setObjectName("searchBar");
    menuLayout->addWidget(searchBar);
    connect(searchBar, &SearchBar::textChanged, app, &MainWindow::searchWidgets);

    QScrollArea* scrollableArea=new QScrollArea;
    scrollableArea->setFrameShape(QFrame::NoFrame);
    menuLayout->addWidget(scrollableArea);
    scrollableArea->setWidgetResizable(true); //Altrimenti, lo scroll si adatta ai widget, e quindi non funziona
    scrollableArea->setWidget(sensorsContainer);
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
