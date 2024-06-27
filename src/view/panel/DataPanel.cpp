#include "DataPanel.h"

#include <QLabel>
#include <QFont>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QPixmap>

DataPanel::DataPanel(AbstractSensor* sensor, QTimer* t) : timer(t), lay(new QVBoxLayout){
    setFocusPolicy(Qt::NoFocus);

    lay->setAlignment(Qt::AlignVCenter);
    setLayout(lay);

    QLabel* sensorName=new QLabel(QString::fromStdString(sensor->getName()));
    sensorName->setAlignment(Qt::AlignLeft);
    QFont fontName=sensorName->font();
    fontName.setPointSize(40);
    fontName.setBold(true);
    sensorName->setFont(fontName);
    lay->addWidget(sensorName);

    QLabel* sensorId=new QLabel(QString::fromStdString(sensor->getId()));
    sensorId->setAlignment(Qt::AlignLeft);
    sensorId->setStyleSheet("color: #6e6e6e");
    lay->addWidget(sensorId);

    sensor->request(this);
}

QChartView* DataPanel::chartView(){
    QChartView* view=new QChartView;
    view->setFocusPolicy(Qt::NoFocus);
    view->setMinimumSize(600,600);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

QChart* DataPanel::chart(){
    QChart* chart=new QChart;
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->setVisible(false);
    return chart;
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

    QStackedLayout* graphLayout=new QStackedLayout;
    lay->addLayout(graphLayout);

    //Grafico co2
    QChart* co2Chart=chart();
    charts.push_back(co2Chart);
    co2Chart->setTitle("CO<sub>2</sub>");
    co2Chart->addSeries(sensor->getCo2Vals());

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setGridLineVisible(false);
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    co2Chart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getCo2Vals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setGridLineVisible(false);
    yAxis1->setTickCount(10);
    yAxis1->setRange(300, 950);
    yAxis1->setTitleText("ppm");
    co2Chart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getCo2Vals()->attachAxis(yAxis1);

    QChartView* co2View=chartView();
    co2View->setChart(co2Chart);
    graphLayout->addWidget(co2View);

    //Grafico PM2.5
    QChart* pm25Chart=chart();
    charts.push_back(pm25Chart);
    pm25Chart->setTitle("PM2.5");
    pm25Chart->addSeries(sensor->getPm25Vals());

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setGridLineVisible(false);
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    pm25Chart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getPm25Vals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setGridLineVisible(false);
    yAxis2->setTickCount(10);
    yAxis2->setRange(0, 35);
    yAxis2->setTitleText("μg/m<sup>3</sup>");
    pm25Chart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getPm25Vals()->attachAxis(yAxis2);

    QChartView* pm25View=chartView();
    pm25View->setChart(pm25Chart);
    graphLayout->addWidget(pm25View);

    //Grafico di PM10
    QChart* pm10Chart=chart();
    charts.push_back(pm10Chart);
    pm10Chart->setTitle("PM10");
    pm10Chart->addSeries(sensor->getPm10Vals());

    QDateTimeAxis* xAxis3=new QDateTimeAxis;
    xAxis3->setGridLineVisible(false);
    xAxis3->setTickCount(10);
    xAxis3->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis3->setFormat("hh.mm");
    xAxis3->setTitleText("Ora");
    pm10Chart->addAxis(xAxis3, Qt::AlignBottom);
    sensor->getPm10Vals()->attachAxis(xAxis3);

    QValueAxis* yAxis3=new QValueAxis;
    yAxis3->setGridLineVisible(false);
    yAxis3->setGridLineVisible(false);
    yAxis3->setTickCount(10);
    yAxis3->setRange(0, 50);
    yAxis3->setTitleText("μg/m<sup>3</sup>");
    pm10Chart->addAxis(yAxis3, Qt::AlignLeft);
    sensor->getPm10Vals()->attachAxis(yAxis3);

    QChartView* pm10View=chartView();
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
    lay->addLayout(buttonLayout);

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

    QStackedLayout* graphLayout=new QStackedLayout;
    lay->addLayout(graphLayout);

    //Grafico watt
    QChart* wattChart=chart();
    charts.push_back(wattChart);
    wattChart->setTitle("Wattaggio istantaneo");
    wattChart->addSeries(sensor->getWattVals());

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setGridLineVisible(false);
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    wattChart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getWattVals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setGridLineVisible(false);
    yAxis1->setTickCount(10);
    yAxis1->setRange(0, 3000);
    yAxis1->setTitleText("Watt");
    wattChart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getWattVals()->attachAxis(yAxis1);

    QChartView* wattView=chartView();
    wattView->setChart(wattChart);
    graphLayout->addWidget(wattView);

    //Grafico volt
    QChart* voltChart=chart();
    charts.push_back(voltChart);
    voltChart->setTitle("Voltaggio istantaneo");
    voltChart->addSeries(sensor->getVoltageVals());

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setGridLineVisible(false);
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    voltChart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getVoltageVals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setGridLineVisible(false);
    yAxis2->setTickCount(10);
    yAxis2->setRange(220, 231);
    yAxis2->setTitleText("Volt");
    voltChart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getVoltageVals()->attachAxis(yAxis2);

    QChartView* voltView=chartView();
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
    lay->addLayout(buttonLayout);

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
    //Grafico pressione
    QChart* pressureChart=chart();
    charts.push_back(pressureChart);
    pressureChart->setTitle("Pressione atmosferica");
    pressureChart->addSeries(sensor->getPressureVals());

    QDateTimeAxis* xAxis=new QDateTimeAxis;
    xAxis->setGridLineVisible(false);
    xAxis->setTickCount(10);
    QDateTime currentTime=QDateTime::currentDateTime();
    xAxis->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis->setFormat("hh.mm");
    xAxis->setTitleText("Ora");
    pressureChart->addAxis(xAxis, Qt::AlignBottom);
    sensor->getPressureVals()->attachAxis(xAxis);

    QValueAxis* yAxis=new QValueAxis;
    yAxis->setGridLineVisible(false);
    yAxis->setTickCount(10);
    yAxis->setRange(0, 1094);
    yAxis->setTitleText("hPa");
    pressureChart->addAxis(yAxis, Qt::AlignLeft);
    sensor->getPressureVals()->attachAxis(yAxis);

    QChartView* pressureView=chartView();
    pressureView->setChart(pressureChart);
    lay->addWidget(pressureView);

    connect(timer, &QTimer::timeout, this, [=](){
        QDateTime currentTime=QDateTime::currentDateTime();
        xAxis->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    });
}

void DataPanel::handle(const TempHumiditySensor* sensor){
    QDateTime currentTime=QDateTime::currentDateTime();

    QStackedLayout* graphLayout=new QStackedLayout;
    lay->addLayout(graphLayout);

    //Grafico Temperatura
    QChart* tempChart=chart();
    charts.push_back(tempChart);
    tempChart->setTitle("Temperatura");
    tempChart->addSeries(sensor->getTemperatureVals());

    QDateTimeAxis* xAxis1=new QDateTimeAxis;
    xAxis1->setGridLineVisible(false);
    xAxis1->setTickCount(10);
    xAxis1->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis1->setFormat("hh.mm");
    xAxis1->setTitleText("Ora");
    tempChart->addAxis(xAxis1, Qt::AlignBottom);
    sensor->getTemperatureVals()->attachAxis(xAxis1);

    QValueAxis* yAxis1=new QValueAxis;
    yAxis1->setGridLineVisible(false);
    yAxis1->setTickCount(10);
    yAxis1->setRange(-10, 35);
    yAxis1->setTitleText("Gradi Celsius");
    tempChart->addAxis(yAxis1, Qt::AlignLeft);
    sensor->getTemperatureVals()->attachAxis(yAxis1);

    QChartView* tempView=chartView();
    tempView->setChart(tempChart);
    graphLayout->addWidget(tempView);

    //Grafico umidità
    QChart* humidityChart=chart();
    charts.push_back(humidityChart);
    humidityChart->setTitle("Umidità");
    humidityChart->addSeries(sensor->getHumidityVals());

    QDateTimeAxis* xAxis2=new QDateTimeAxis;
    xAxis2->setGridLineVisible(false);
    xAxis2->setTickCount(10);
    xAxis2->setRange(currentTime.addSecs(-(timer->interval()/1000)*15),currentTime);
    xAxis2->setFormat("hh.mm");
    xAxis2->setTitleText("Ora");
    humidityChart->addAxis(xAxis2, Qt::AlignBottom);
    sensor->getHumidityVals()->attachAxis(xAxis2);

    QValueAxis* yAxis2=new QValueAxis;
    yAxis2->setGridLineVisible(false);
    yAxis2->setTickCount(10);
    yAxis2->setRange(0, 100);
    yAxis2->setTitleText("Percentuale");
    humidityChart->addAxis(yAxis2, Qt::AlignLeft);
    sensor->getHumidityVals()->attachAxis(yAxis2);

    QChartView* humidityView=chartView();
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
    lay->addLayout(buttonLayout);

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
    delete lay;
}