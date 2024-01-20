#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>

#include <QVBoxLayout>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), menuBar(new QMenuBar()), sensorMenu(new SensorMenu()){
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

    //Connessione delle actions agli slots
    connect(newFile, &QAction::triggered, this, &MainWindow::newFile);
    connect(openFile, &QAction::triggered, this, &MainWindow::openFile);
    connect(openFile, &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::setupUI(){
    addDockWidget(Qt::LeftDockWidgetArea, sensorMenu);
    QWidget* test=new QWidget();
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(new QLineEdit());
    test->setLayout(layout);
    setCentralWidget(test);
}

//Slots config
void MainWindow::newFile(){
    //TODO
}

void MainWindow::openFile(){
    QString path=QFileDialog::getOpenFileName(this, ("Apri file"), QDir::homePath(),  "JSON Files (*.json)");
}

void MainWindow::saveFile(){
    //TODO
}
