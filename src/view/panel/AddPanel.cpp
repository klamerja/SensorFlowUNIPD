#include "AddPanel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>

#include "../MainWindow.h"

AddPanel::AddPanel(MainWindow* main): QDialog(main), app(main), nameEdit(new QLineEdit), typeSelection(new QComboBox){
    setModal(true);
    setWindowFlag(Qt::FramelessWindowHint);

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    //Creazione Form
    QFormLayout* formLayout=new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignLeft);

    //Name Edit
    formLayout->addRow("Nome", nameEdit);

    //Type selection
    typeSelection->setInsertPolicy(QComboBox::InsertAlphabetically);
    typeSelection->setFrame(false);
    typeSelection->addItem("Qualità dell'aria");
    typeSelection->addItem("Elettricità");
    typeSelection->addItem("Pressione atmosferica");
    typeSelection->addItem("Temperatura e umidità");
    formLayout->addRow("Tipologia di sensore", typeSelection);

    //Submit Button
    QPushButton* submitButton=new QPushButton("Crea sensore");
    submitButton->setDefault(true);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->addWidget(submitButton);

    //Connessione del submit
    connect(this, &QDialog::rejected, this, &AddPanel::onReject);
    connect(submitButton, &QPushButton::clicked, this, &AddPanel::onSubmit);

    //Composizione form
    layout->addLayout(formLayout);
    layout->addLayout(buttonLayout);

    //Impostazione della fixed size del Dialog
    setFixedSize(sizeHint());
}

void AddPanel::onReject(){
    app->setHomePanel();
}

void AddPanel::onSubmit(){
    if(!nameEdit->text().isEmpty()){
        app->addSensor(nameEdit->text(), typeSelection->currentIndex());
        done(QDialog::Accepted);
        app->setHomePanel();
    }else{
        QMessageBox error(this);
        error.setStandardButtons(QMessageBox::Close);
        error.setModal(true);
        error.setWindowFlag(Qt::FramelessWindowHint);
        error.setText("Per favore inserire un nome");
        error.exec();
    }
}
