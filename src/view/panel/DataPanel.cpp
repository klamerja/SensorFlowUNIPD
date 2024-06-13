#include "DataPanel.h"

#include <QStackedLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QPixmap>

DataPanel::DataPanel(AbstractSensor* sensor, QTimer* t) : timer(t){
    setFocusPolicy(Qt::NoFocus);
    sensor->request(this);
}

QChartView* DataPanel::chart(){
    QChartView* view=new QChartView;
    view->setFocusPolicy(Qt::NoFocus);
    view->setMinimumSize(600,600);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

QPushButton* DataPanel::leftBtn(){
    QPushButton* button=new QPushButton;
    button->setIcon(QIcon(":/assets/left.svg"));
    button->setFixedSize(50,50);
    button->setFlat(true);
    button->setIconSize(QSize(25,25));
    button->setFocusPolicy(Qt::NoFocus);
    return button;
}

QPushButton* DataPanel::rightBtn(){
    QPushButton* button=new QPushButton;
    button->setIcon(QIcon(":/assets/right.svg"));
    button->setFixedSize(50,50);
    button->setFlat(true);
    button->setIconSize(QSize(25,25));
    button->setFocusPolicy(Qt::NoFocus);
    return button;
}

void DataPanel::handle(const AirQualitySensor* sensor){
    QDateTime currentTime=QDateTime::currentDateTime();

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    QStackedLayout* graphLayout=new QStackedLayout;
    layout->addLayout(graphLayout);

    //Grafico co2
    QChart* co2Chart=new QChart;
    co2Chart->setBackgroundBrush(Qt::transparent);
    charts.push_back(co2Chart);
    co2Chart->setAnimationOptions(QChart::AllAnimations);

    co2Chart->addSeries(sensor->getCo2Vals());
    co2Chart->setTitle("CO2");
    co2Chart->legend()->hide();

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    co2Chart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getCo2Vals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setTickCount(10);
    yAxis1->setRange(300, 950);
    yAxis1->setTitleText("ppm");
    co2Chart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getCo2Vals()->attachAxis(yAxis1);

    QChartView* co2View=chart();
    co2View->setChart(co2Chart);
    graphLayout->addWidget(co2View);

    //Grafico PM2.5
    QChart* pm25Chart=new QChart;
    charts.push_back(pm25Chart);
    pm25Chart->setAnimationOptions(QChart::AllAnimations);
    pm25Chart->addSeries(sensor->getPm25Vals());
    pm25Chart->setTitle("PM2.5");
    pm25Chart->legend()->hide();

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    pm25Chart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getPm25Vals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setTickCount(10);
    yAxis2->setRange(0, 35);
    yAxis2->setTitleText("μg/m3");
    pm25Chart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getPm25Vals()->attachAxis(yAxis2);

    QChartView* pm25View=chart();
    pm25View->setChart(pm25Chart);
    graphLayout->addWidget(pm25View);

    //Grafico di PM10
    QChart* pm10Chart=new QChart;
    charts.push_back(pm10Chart);
    pm10Chart->setAnimationOptions(QChart::AllAnimations);
    pm10Chart->addSeries(sensor->getPm10Vals());
    pm10Chart->setTitle("PM10");
    pm10Chart->legend()->hide();

    QDateTimeAxis* xAxis3=new QDateTimeAxis;
    xAxis3->setTickCount(10);
    xAxis3->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis3->setFormat("hh.mm");
    xAxis3->setTitleText("Ora");
    pm10Chart->addAxis(xAxis3, Qt::AlignBottom);
    sensor->getPm10Vals()->attachAxis(xAxis3);

    QValueAxis* yAxis3=new QValueAxis;
    yAxis3->setTickCount(10);
    yAxis3->setRange(0, 50);
    yAxis3->setTitleText("μg/m3");
    pm10Chart->addAxis(yAxis3, Qt::AlignLeft);
    sensor->getPm10Vals()->attachAxis(yAxis3);

    QChartView* pm10View=chart();
    pm10View->setChart(pm10Chart);
    graphLayout->addWidget(pm10View);

    connect(timer, &QTimer::timeout, this, [=](){
        QDateTime currentTime=QDateTime::currentDateTime();
        xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
        xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
        xAxis3->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    });

    //Slide Stack
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(buttonLayout);

    QPushButton* leftButton=leftBtn();
    QPushButton* rightButton=rightBtn();
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    connect(leftButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=0)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()-1);
        else
            graphLayout->setCurrentIndex(graphLayout->count()-1);
    });

    connect(rightButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=graphLayout->count()-1)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()+1);
        else
            graphLayout->setCurrentIndex(0);
    });
}

void DataPanel::handle(const ElectricitySensor* sensor){
    QDateTime currentTime=QDateTime::currentDateTime();

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    QStackedLayout* graphLayout=new QStackedLayout;
    layout->addLayout(graphLayout);

    //Grafico watt
    QChart* wattChart=new QChart;
    charts.push_back(wattChart);
    wattChart->setAnimationOptions(QChart::AllAnimations);
    wattChart->addSeries(sensor->getWattVals());
    wattChart->setTitle("Wattaggio");
    wattChart->legend()->hide();

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    wattChart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getWattVals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setTickCount(10);
    yAxis1->setRange(0, 3000);
    yAxis1->setTitleText("Watt");
    wattChart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getWattVals()->attachAxis(yAxis1);

    QChartView* wattView=chart();
    wattView->setChart(wattChart);
    graphLayout->addWidget(wattView);

    //Grafico volt
    QChart* voltChart=new QChart;
    charts.push_back(voltChart);
    voltChart->setAnimationOptions(QChart::AllAnimations);
    voltChart->addSeries(sensor->getVoltageVals());
    voltChart->setTitle("Voltaggio");
    voltChart->legend()->hide();

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    voltChart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getVoltageVals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setTickCount(10);
    yAxis2->setRange(220, 231);
    yAxis2->setTitleText("μg/m3");
    voltChart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getVoltageVals()->attachAxis(yAxis2);

    QChartView* voltView=chart();
    voltView->setChart(voltChart);
    graphLayout->addWidget(voltView);

    connect(timer, &QTimer::timeout, this, [=](){
        QDateTime currentTime=QDateTime::currentDateTime();
        xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
        xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    });

    //Slide Stack
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(buttonLayout);

    QPushButton* leftButton=leftBtn();
    QPushButton* rightButton=rightBtn();
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    connect(leftButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=0)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()-1);
        else
            graphLayout->setCurrentIndex(graphLayout->count()-1);
    });

    connect(rightButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=graphLayout->count()-1)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()+1);
        else
            graphLayout->setCurrentIndex(0);
    });
}

void DataPanel::handle(const PressureSensor* sensor){
    QHBoxLayout* layout=new QHBoxLayout;
    setLayout(layout);

    //Grafico pressione
    QChart* pressureChart=new QChart;
    charts.push_back(pressureChart);
    pressureChart->setAnimationOptions(QChart::AllAnimations);
    pressureChart->addSeries(sensor->getPressureVals());
    pressureChart->setTitle("Pressione dell'aria");
    pressureChart->legend()->hide();

    QDateTimeAxis* xAxis=new QDateTimeAxis;
    xAxis->setTickCount(10);
    QDateTime currentTime=QDateTime::currentDateTime();
    xAxis->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis->setFormat("hh.mm");
    xAxis->setTitleText("Ora");
    pressureChart->addAxis(xAxis, Qt::AlignBottom);
    sensor->getPressureVals()->attachAxis(xAxis); //Inserito altrimenti non fa il repaint con la modifica

    QValueAxis* yAxis=new QValueAxis;
    yAxis->setTickCount(10);
    yAxis->setRange(0, 1094);
    yAxis->setTitleText("hPa");
    pressureChart->addAxis(yAxis, Qt::AlignLeft);
    sensor->getPressureVals()->attachAxis(yAxis);

    QChartView* pressureView=chart();
    pressureView->setChart(pressureChart);
    layout->addWidget(pressureView);

    connect(timer, &QTimer::timeout, this, [=](){
        QDateTime currentTime=QDateTime::currentDateTime();
        xAxis->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    });
}

void DataPanel::handle(const TempHumiditySensor* sensor){
    QDateTime currentTime=QDateTime::currentDateTime();

    QVBoxLayout* layout=new QVBoxLayout;
    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

    QStackedLayout* graphLayout=new QStackedLayout;
    layout->addLayout(graphLayout);

    //Grafico Temperatura
    QChart* tempChart=new QChart;
    charts.push_back(tempChart);
    tempChart->setAnimationOptions(QChart::AllAnimations);
    tempChart->addSeries(sensor->getTemperatureVals());
    tempChart->setTitle("Temperatura");
    tempChart->legend()->hide();

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    tempChart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getTemperatureVals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setTickCount(10);
    yAxis1->setRange(-10, 35);
    yAxis1->setTitleText("Gradi(C)");
    tempChart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getTemperatureVals()->attachAxis(yAxis1);

    QChartView* tempView=chart();
    tempView->setChart(tempChart);
    graphLayout->addWidget(tempView);

    //Grafico umidità
    QChart* humidityChart=new QChart;
    charts.push_back(humidityChart);
    humidityChart->setAnimationOptions(QChart::AllAnimations);
    humidityChart->addSeries(sensor->getHumidityVals());
    humidityChart->setTitle("Umidità");
    humidityChart->legend()->hide();

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    humidityChart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getHumidityVals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setTickCount(10);
    yAxis2->setRange(0, 100);
    yAxis2->setTitleText("%");
    humidityChart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getHumidityVals()->attachAxis(yAxis2);

    QChartView* humidityView=chart();
    humidityView->setChart(humidityChart);
    graphLayout->addWidget(humidityView);

    connect(timer, &QTimer::timeout, this, [=](){
        QDateTime currentTime=QDateTime::currentDateTime();
        xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
        xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    });

    //Slide Stack
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(buttonLayout);

    QPushButton* leftButton=leftBtn();
    QPushButton* rightButton=rightBtn();
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    connect(leftButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=0)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()-1);
        else
            graphLayout->setCurrentIndex(graphLayout->count()-1);
    });

    connect(rightButton, &QPushButton::clicked, this, [=](){
        if(graphLayout->currentIndex()!=graphLayout->count()-1)
            graphLayout->setCurrentIndex(graphLayout->currentIndex()+1);
        else
            graphLayout->setCurrentIndex(0);
    });
}

DataPanel::~DataPanel(){
    for(QChart* chart:charts){
        for(QAbstractSeries* series:chart->series()){
            chart->removeSeries(series);
        }
    }
    delete layout();
}