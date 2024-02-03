#include "MainWindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

#include <QLineEdit>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), controller(new Controller(this)), menuBar(new QMenuBar()), sensorMenu(new SensorMenu(this)){
    createMenu();
    setupUI();
}

//Graphical setup
void MainWindow::createMenu(){
    setMenuBar(menuBar);

    //File Menu
    QMenu* fileMenu=menuBar->addMenu("File");
    QAction* newFile=fileMenu->addAction("Nuovo");
    newFile->setShortcut(Qt::CTRL | Qt::Key_N);
    QAction* openFile=fileMenu->addAction("Apri");
    openFile->setShortcut(Qt::CTRL | Qt::Key_A);
    QAction* saveFile=fileMenu->addAction("Salva");
    saveFile->setShortcut(Qt::CTRL | Qt::Key_S);

    //Sensors Menu
    QMenu* sensorsMenu=menuBar->addMenu("Sensori");
    QAction* newSensor=sensorsMenu->addAction("Aggiungi sensore");
    newSensor->setShortcut(Qt::CTRL | Qt::Key_T);
    QAction* deleteSensor=sensorsMenu->addAction("Rimuovi sensore");
    deleteSensor->setShortcut(Qt::CTRL | Qt::Key_Backspace);

    //Connessione delle actions agli slots
    connect(newFile, &QAction::triggered, controller, &Controller::newFile);
    connect(openFile, &QAction::triggered, controller, &Controller::openFile);
    connect(saveFile, &QAction::triggered, controller, &Controller::saveFile);
    connect(newSensor, &QAction::triggered, controller, &Controller::newSensor);
    connect(deleteSensor, &QAction::triggered, controller, &Controller::deleteSensor);
}

void MainWindow::setupUI(){
    addDockWidget(Qt::LeftDockWidgetArea, sensorMenu);
    QWidget* test=new QWidget();
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(new QLineEdit());
    test->setLayout(layout);
    setCentralWidget(test);
}

void MainWindow::onItemClicked(){
    qWarning()<<"Andata";
}
