#include "interface.h"
#include <QLayout>
#include <QFileDialog>
#include <fstream>


interface::interface(QWidget *parent)
    : QWidget(parent), sys_(nullptr)
{

    scatter = new Q3DScatter;
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    scatter->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    pointseries = new QScatter3DSeries;
    point << QVector3D(0, 0, 0);
    pointseries->dataProxy()->addItems(point);
    //scatter->seriesList()->dataProxy()->addItems(point);
    pointseries->setBaseColor(Qt::red);
    scatter->addSeries(pointseries);
    pointseries->setMeshSmooth(true);

    series = nullptr;


    Xaxis = new QValue3DAxis;
    Xaxis->setTitle("X, нм");
    Xaxis->setTitleVisible(true);

    Yaxis = new QValue3DAxis;
    Yaxis->setTitle("Y, нм");
    Yaxis->setTitleVisible(true);

    Zaxis = new QValue3DAxis;
    Zaxis->setTitle("Z, нм");
    Zaxis->setTitleVisible(true);

    scatter->setAxisX(Xaxis);
    scatter->setAxisY(Yaxis);
    scatter->setAxisZ(Zaxis);

    scatter->setAspectRatio(1.0);
    scatter->setHorizontalAspectRatio(1.0);
    /*data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
    series->dataProxy()->addItems(data);
    scatter->addSeries(series);*/


    timer = new QTimer;
    timer->setInterval(10);


    labelQ = new QLabel("Q(В единицах заряда электрона)");
    labelgamma = new QLabel("Gamma(В единицах удельного заряда электрона)");
    labelP = new QLabel("P(1e-30 Кл*м)");
    labelX0 = new QLabel("X0(нм)");
    labelY0 = new QLabel("Y0(нм)");
    labelZ0 = new QLabel("Z0(нм)");
    labelUx0 = new QLabel("Ux0(м/с)");
    labelUy0 = new QLabel("Uy0(м/с)");
    labelUz0 = new QLabel("Uz0(м/с)");

    doubleSpinBoxQ = new QDoubleSpinBox;
    doubleSpinBoxgamma = new QDoubleSpinBox;
    doubleSpinBoxP = new QDoubleSpinBox;
    doubleSpinBoxX0 = new QDoubleSpinBox;
    doubleSpinBoxY0 = new QDoubleSpinBox;
    doubleSpinBoxZ0 = new QDoubleSpinBox;
    doubleSpinBoxUx0 = new QDoubleSpinBox;
    doubleSpinBoxUy0 = new QDoubleSpinBox;
    doubleSpinBoxUz0 = new QDoubleSpinBox;

    pushButtonStart = new QPushButton("Start");
    pushButtonStop = new QPushButton("Stop");
    textEditLog = new QTextEdit;


    doubleSpinBoxUx0->setMaximum(10000000.0);
    doubleSpinBoxUy0->setMaximum(10000000.0);
    doubleSpinBoxUz0->setMaximum(10000000.0);
    doubleSpinBoxUx0->setMinimum(-10000000.0);
    doubleSpinBoxUy0->setMinimum(-10000000.0);
    doubleSpinBoxUz0->setMinimum(-10000000.0);
    doubleSpinBoxQ->setMaximum(1000.0);
    doubleSpinBoxQ->setMinimum(-1000.0);
    doubleSpinBoxgamma->setMaximum(1000.0);
    doubleSpinBoxgamma->setMinimum(-1000.0);
    doubleSpinBoxP->setMaximum(100000);
    doubleSpinBoxP->setMinimum(-100000);

    doubleSpinBoxQ->setValue(-1.0);
    doubleSpinBoxgamma->setValue(1.0);
    doubleSpinBoxY0->setValue(1.0);
    doubleSpinBoxUx0->setValue(203428);
    doubleSpinBoxUz0->setValue(0);
    doubleSpinBoxP->setValue(0);


    textEditLog->setReadOnly(true);


    QGridLayout *layoutParameters = new QGridLayout;
    layoutParameters->addWidget(labelQ, 0, 0);
    layoutParameters->addWidget(labelgamma, 1, 0);
    layoutParameters->addWidget(labelP, 2, 0);
    layoutParameters->addWidget(doubleSpinBoxQ, 0, 1);
    layoutParameters->addWidget(doubleSpinBoxgamma, 1, 1);
    layoutParameters->addWidget(doubleSpinBoxP, 2, 1);
    layoutParameters->addWidget(labelX0, 0, 2);
    layoutParameters->addWidget(labelY0, 1, 2);
    layoutParameters->addWidget(labelZ0, 2, 2);
    layoutParameters->addWidget(doubleSpinBoxX0, 0, 3);
    layoutParameters->addWidget(doubleSpinBoxY0, 1, 3);
    layoutParameters->addWidget(doubleSpinBoxZ0, 2, 3);
    layoutParameters->addWidget(labelUx0, 0, 4);
    layoutParameters->addWidget(labelUy0, 1, 4);
    layoutParameters->addWidget(labelUz0, 2, 4);
    layoutParameters->addWidget(doubleSpinBoxUx0, 0, 5);
    layoutParameters->addWidget(doubleSpinBoxUy0, 1, 5);
    layoutParameters->addWidget(doubleSpinBoxUz0, 2, 5);


    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(pushButtonStart);
    layoutButtons->addWidget(pushButtonStop);

    QVBoxLayout *layoutLeft = new QVBoxLayout;
    layoutLeft->addLayout(layoutParameters);
    layoutLeft->addLayout(layoutButtons);
    //layoutLeft->addWidget(textEditLog);

    QVBoxLayout *layoutPlot = new QVBoxLayout;
    layoutPlot->addWidget(QWidget::createWindowContainer(scatter, this));

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutPlot);

    /*QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutParameters);
    layoutMain->addLayout(layoutButtons);
    layoutMain->addWidget(textEditLog);*/

    this->setLayout(layoutMain);

    connect(pushButtonStart, &QPushButton::clicked, this, &interface::startCalculation);
    connect(pushButtonStop, &QPushButton::clicked, this, &interface::stopCalculation);
    connect(timer, &QTimer::timeout, this, &interface::makeStep);
}

interface::~interface()
{
}

void interface::startCalculation()
{

    data.clear();
    scatter->removeSeries(series);
    series = new QScatter3DSeries;

    textEditLog->clear();
    std::map<std::string, double> params{
        {"Q", doubleSpinBoxQ->value()},
        {"Gamma", doubleSpinBoxgamma->value()},
        {"P", doubleSpinBoxP->value()},
        {"X0", doubleSpinBoxX0->value()},
        {"Y0", doubleSpinBoxY0->value()},
        {"Z0", doubleSpinBoxZ0->value()},
        {"Ux0", doubleSpinBoxUx0->value()},
        {"Uy0", doubleSpinBoxUy0->value()},
        {"Uz0", doubleSpinBoxUz0->value()}
    };
    doubleSpinBoxP->setEnabled(false);
    doubleSpinBoxgamma->setEnabled(false);
    doubleSpinBoxQ->setEnabled(false);
    doubleSpinBoxX0->setEnabled(false);
    doubleSpinBoxY0->setEnabled(false);
    doubleSpinBoxZ0->setEnabled(false);
    doubleSpinBoxUx0->setEnabled(false);
    doubleSpinBoxUy0->setEnabled(false);
    doubleSpinBoxUz0->setEnabled(false);

    pushButtonStart->setEnabled(false);
    pushButtonStop->setEnabled(true);
    sys_ = new System(params);

    textEditLog->append(QString::number(sys_->T()));
    timer->start();

}

void interface::stopCalculation()
{
    timer->stop();

    doubleSpinBoxP->setEnabled(true);
    doubleSpinBoxgamma->setEnabled(true);
    doubleSpinBoxQ->setEnabled(true);
    doubleSpinBoxX0->setEnabled(true);
    doubleSpinBoxY0->setEnabled(true);
    doubleSpinBoxZ0->setEnabled(true);
    doubleSpinBoxUx0->setEnabled(true);
    doubleSpinBoxUy0->setEnabled(true);
    doubleSpinBoxUz0->setEnabled(true);

    pushButtonStart->setEnabled(true);
    pushButtonStop->setEnabled(false);

    /*QString file_name = QFileDialog::getSaveFileName(this, "Save data", "DataProg.txt");
    std::ofstream out_file(file_name.toStdString(), binary)*/
}

void interface::makeStep()
{
    System *sys1 = sys_;
    double dt = 3.92e-17;
    sys_->RK4_step(dt);
    if(sys_->R().length() >= 1e-10)
    //if(abs(sys1->LOEC() - sys_->LOEC())>1e6)
    {
        dt = 3.92e-18;
        sys_ = sys1;
        sys_->RK4_step(dt);
    }

    data << QVector3D(1e9*sys_->X(), 1e9*sys_->Y(), 1e9*sys_->Z());
    series->dataProxy()->addItems(data);
    scatter->addSeries(series);
    series->setMesh(QAbstract3DSeries::MeshPoint);
    series->setMeshSmooth(true);
    data.clear();
    dt = 3.92e-17;


    /*textEditLog->append(QString::number(sys_->X()) + ' '
                        + QString::number(sys_->Y()) + ' '
                        + QString::number(sys_->Z()));*/
}
