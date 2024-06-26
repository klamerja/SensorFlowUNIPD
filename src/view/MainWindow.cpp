#include "MainWindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "panel/HomePanel.h"
#include "panel/DataPanel.h"
#include "panel/AddPanel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), controller(new Controller(this)), menuBar(new QMenuBar()), sensorMenu(new SensorMenu(this)), panel(new QWidget), itemFocused(nullptr){
    createMenu();
    setupUI();
}

void MainWindow::removeFocusedItem(){
    itemFocused=nullptr;
    setHomePanel();
}

void MainWindow::createMenu(){
    menuBar->setFocusPolicy(Qt::NoFocus);
    setMenuBar(menuBar);

    //File Menu
    QMenu* fileMenu=menuBar->addMenu("File");
    fileMenu->setFocusPolicy(Qt::NoFocus);
    QAction* newFile=fileMenu->addAction("Nuovo");
    newFile->setShortcut(Qt::CTRL | Qt::Key_N);
    QAction* openFile=fileMenu->addAction("Apri");
    openFile->setShortcut(Qt::CTRL | Qt::Key_O);
    QAction* saveFile=fileMenu->addAction("Salva");
    saveFile->setShortcut(Qt::CTRL | Qt::Key_S);

    //Sensors Menu
    QMenu* sensorsMenu=menuBar->addMenu("Sensori");
    sensorsMenu->setFocusPolicy(Qt::NoFocus);
    QAction* newSensor=sensorsMenu->addAction("Aggiungi sensore");
    newSensor->setShortcut(Qt::CTRL | Qt::Key_T);
    QAction* deleteSensor=sensorsMenu->addAction("Rimuovi sensore");
    deleteSensor->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Backspace);

    //Connessione delle actions agli slots
    connect(newFile, &QAction::triggered, controller, &Controller::newFile);
    connect(openFile, &QAction::triggered, controller, &Controller::openFile);
    connect(saveFile, &QAction::triggered, controller, &Controller::saveFile);
    connect(newSensor, &QAction::triggered, this, &MainWindow::newSensor);
    connect(deleteSensor, &QAction::triggered, this, &MainWindow::removeSensor);
}

void MainWindow::setupUI(){
    //Dimensione minima del panel
    QHBoxLayout* hLayout=new QHBoxLayout;
    QVBoxLayout* vLayout=new QVBoxLayout;
    hLayout->setAlignment(Qt::AlignHCenter);
    vLayout->setAlignment(Qt::AlignVCenter);
    vLayout->addWidget(panel);
    hLayout->addLayout(vLayout);
    QWidget* panelContainer=new QWidget;
    panelContainer->setLayout(hLayout);

    QWidget* window=new QWidget;
    QHBoxLayout* windowLayout=new QHBoxLayout;
    setCentralWidget(window);
    window->setLayout(windowLayout);

    windowLayout->addWidget(sensorMenu);
    windowLayout->addWidget(panelContainer);
    setHomePanel();
}

void MainWindow::addSensor(const QString& name, int type, int distribution){
    controller->addSensor(name, type, distribution);
}

void MainWindow::repaintSensorsList(std::vector<AbstractSensor*> sensors){
    sensorMenu->paintSensors(sensors);
}

void MainWindow::deleteSensor(ItemCard* item){
    setHomePanel();
    controller->deleteSensor(item->getSensor());
    delete item;
    if(itemFocused==item)itemFocused=nullptr;
}

void MainWindow::setHomePanel(){
    if(panel->layout()){
        delete panel->layout()->takeAt(0)->widget();
        delete panel->layout();
    }
    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(new HomePanel);
    panel->setLayout(layout);
}

void MainWindow::refreshSensorsList(){
    controller->refreshSensorsList();
}

//SLOTS
void MainWindow::newSensor(){
    if(controller->isJsonInstanced()){
        if(itemFocused){
            itemFocused->clearFocus();
            removeFocusedItem();
        }
        setHomePanel();
        AddPanel addPanel(this);
        addPanel.exec();
    }else{
        QMessageBox warning;
        warning.setModal(true);
        warning.setText("File non aperto");
        warning.setIcon(QMessageBox::Critical);
        warning.addButton(QMessageBox::Ok);
        warning.exec();
    }
}

void MainWindow::removeSensor(){
    if(itemFocused){
        controller->deleteSensor(itemFocused->getSensor());
        delete itemFocused;
        removeFocusedItem();
    }
    if(!controller->isJsonInstanced()){
        QMessageBox warning;
        warning.setModal(true);
        warning.setText("File non aperto");
        warning.setIcon(QMessageBox::Critical);
        warning.addButton(QMessageBox::Ok);
        warning.exec();
    }
}

void MainWindow::onItemClicked(ItemCard* item){
    if(panel->layout()){
        delete panel->layout()->takeAt(0)->widget();
        delete panel->layout();
    }
    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(new DataPanel(item->getSensor(), controller->getTimer()));
    panel->setLayout(layout);
    itemFocused=item;
}

void MainWindow::searchWidgets(const QString& text) const{
    controller->searchWidgets(text);
}

bool MainWindow::event(QEvent* event){
    if(event->type()==QEvent::ApplicationPaletteChange){
        emit themeChanged();
    }
    return QMainWindow::event(event);
}

