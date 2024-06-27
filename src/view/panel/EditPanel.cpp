#include "EditPanel.h"
#include "../MainWindow.h"

#include <QFormLayout>
#include <QString>
#include <QMessageBox>

EditPanel::EditPanel(MainWindow* main, AbstractSensor* sens) : QDialog(main), app(main), sensor(sens), nameEdit(new QLineEdit), distributionSelection(new QComboBox){
    setModal(true);
    setWindowTitle("Modifica di " + QString::fromStdString(sensor->getName()));

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    //Creazione Form
    QFormLayout* formLayout=new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignLeft);

    //Name Edit
    nameEdit->setFixedWidth(220);
    nameEdit->setText(QString::fromStdString(sensor->getName()));
    formLayout->addRow("Nome", nameEdit);

    //Distribution selection
    distributionSelection->setInsertPolicy(QComboBox::InsertAlphabetically);
    distributionSelection->setFrame(true);
    distributionSelection->addItem("Casuale");
    distributionSelection->addItem("Gaussiana");
    distributionSelection->addItem("Uniforme");
    distributionSelection->setFixedWidth(220);
    distributionSelection->setCurrentIndex(sensor->getDistribution());
    formLayout->addRow("Distribuzione", distributionSelection);

    //Submit Button
    QPushButton* submitButton=new QPushButton("Modifica sensore");
    submitButton->setDefault(true);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->addWidget(submitButton);

    //Connessione del submit
    connect(this, &QDialog::rejected, this, &EditPanel::onReject);
    connect(submitButton, &QPushButton::clicked, this, &EditPanel::onSubmit);
    
    //Composizione form
    layout->addLayout(formLayout);
    layout->addLayout(buttonLayout);

    //Impostazione della fixed size del Dialog
    setFixedSize(sizeHint());
}

void EditPanel::onReject(){
    app->setHomePanel();
}

void EditPanel::onSubmit(){
    if(!nameEdit->text().isEmpty()){
        sensor->setName(nameEdit->text().toStdString());
        sensor->setDistribution(distributionSelection->currentIndex());
        done(QDialog::Accepted);
        app->refreshSensorsList();
    }else{
        QMessageBox error;
        setModal(true);
        error.setText("Per favore inserire un nome");
        error.setIcon(QMessageBox::Critical);
        error.addButton(QMessageBox::Ok);
        error.exec();
    }
}
