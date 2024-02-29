#include "HomePanel.h"

#include <QPixmap>
#include <QHBoxLayout>

HomePanel::HomePanel() : logoLabel(new QLabel){
    logoLabel=new QLabel;
    logoLabel->setScaledContents(true);
    logoLabel->setFixedSize(200,200);
    QPixmap logo(":/assets/logo.png");
    logoLabel->setPixmap(logo);
    QHBoxLayout* layout=new QHBoxLayout;
    layout->setAlignment(Qt::AlignHCenter);
    setLayout(layout);
    layout->addWidget(logoLabel);
}

HomePanel::~HomePanel(){
    //Attenzione a come si cancella!
    delete layout();
}
