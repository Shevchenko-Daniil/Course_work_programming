#include "interface.h"

#include <QApplication>
#include <QtDataVisualization>

//using namespace QtDataVisualization;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*Q3DScatter scatter;
    scatter.setFlags(scatter.flags() ^ Qt::FramelessWindowHint);
    QScatter3DSeries *series = new QScatter3DSeries;
    QScatterDataArray data;
    System s;
    double dt = 3.92e-17;
    for(int i =0; i<500; ++i){
        s.RK4_step(dt);
        data << QVector3D(s.X(), s.Y(), s.Z());
    }
    series->dataProxy()->addItems(data);
    scatter.addSeries(series);
    scatter.show();*/

    interface w;
    w.show();
    return a.exec();
}
