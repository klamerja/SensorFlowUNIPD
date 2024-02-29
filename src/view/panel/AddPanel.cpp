#include "AddPanel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include "../MainWindow.h"


AddPanel::AddPanel(MainWindow* main):app(main), nameEdit(new QLineEdit), typeSelection(new QComboBox){
    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    //Creazione Form
    QFormLayout* formLayout=new QFormLayout;

    //Name Edit
    formLayout->addRow("Nome", nameEdit);

    //Type selection
    typeSelection->addItem("Qualità dell'aria");
    typeSelection->addItem("Elettricità");
    typeSelection->addItem("Pressione atmosferica");
    typeSelection->addItem("Temperatura e umidità");
    formLayout->addRow("Tipologia di sensore", typeSelection);

    //Submit Button
    QPushButton* submitButton=new QPushButton("Crea sensore");
    submitButton->setFixedWidth(200);
    submitButton->setDefault(true);
    submitButton->setShortcut(Qt::Key_Space);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->addWidget(submitButton);

    //Connessione del submit
    connect(submitButton, &QPushButton::clicked, this, &AddPanel::submit);

    //Composizione form
    layout->addLayout(formLayout);
    layout->addLayout(buttonLayout);
}

void AddPanel::submit(){
    if(!nameEdit->text().isEmpty()){
        app->addSensor(nameEdit->text(),typeSelection->currentIndex());
        app->setHomePanel();
    }else{
        QMessageBox error;
        error.setText("Per favore inserire un nome");
        QPixmap errorIcon(":/assets/Error.png");
        error.setIconPixmap(errorIcon);
        error.exec();
    }
}
