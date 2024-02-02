#include "SensorMenu.h"
#include "ItemCard.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

SensorMenu::SensorMenu(MainWindow* main) : app(main){
    //Config della Dock
    setTitleBarWidget(new QWidget);

    //Layout del pannello sensori
    QScrollArea* scrollableArea=new QScrollArea;
    scrollableArea->setWidgetResizable(true); //Altrimenti, lo scroll si adatta ai widget, e quindi non funziona
    setWidget(scrollableArea);
    QWidget* container=new QWidget;
    QVBoxLayout* layout=new QVBoxLayout;
    container->setLayout(layout);
    scrollableArea->setWidget(container);

    ItemCard* item=new ItemCard(new AirQualitySensor("Stai zitto", new QTimer, "1"), app);
    layout->addWidget(item);
    layout->addStretch();
}
