#include "AddPanel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>

#include "../MainWindow.h"

AddPanel::AddPanel(MainWindow* main): QDialog(main), app(main), nameEdit(new QLineEdit), typeSelection(new QComboBox), distributionSelection(new QComboBox){
    setModal(true);
    setWindowTitle("Inserisci un sensore");

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    //Creazione Form
    QFormLayout* formLayout=new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignLeft);

    //Name Edit
    nameEdit->setFixedWidth(220);
    formLayout->addRow("Nome", nameEdit);

    //Type selection
    typeSelection->setInsertPolicy(QComboBox::InsertAlphabetically);
    typeSelection->setFrame(true);
    typeSelection->addItem("Qualità dell'aria");
    typeSelection->addItem("Elettricità");
    typeSelection->addItem("Pressione atmosferica");
    typeSelection->addItem("Temperatura e umidità");
    typeSelection->setFixedWidth(220);
    formLayout->addRow("Tipologia di sensore", typeSelection);

    //Distribution selection
    distributionSelection->setInsertPolicy(QComboBox::InsertAlphabetically);
    distributionSelection->setFrame(true);
    distributionSelection->addItem("Casuale");
    distributionSelection->addItem("Gaussiana");
    distributionSelection->addItem("Uniforme");
    distributionSelection->setFixedWidth(220);
    formLayout->addRow("Distribuzione", distributionSelection);

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
        app->addSensor(nameEdit->text(), typeSelection->currentIndex(), distributionSelection->currentIndex());
        done(QDialog::Accepted);
    }else{
        QMessageBox error;
        error.setModal(true);
        error.setText("Per favore inserire un nome");
        error.setIcon(QMessageBox::Critical);
        error.addButton(QMessageBox::Ok);
        error.exec();
    }
}
