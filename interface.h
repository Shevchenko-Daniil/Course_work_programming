#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QtDataVisualization>

#include "system.h"
#include "vector3D.h"


class interface : public QWidget
{
    Q_OBJECT

public:
    interface(QWidget *parent = nullptr);
    ~interface();

public slots:
    void startCalculation();
    void stopCalculation();
    void makeStep();

private:
    System *sys_;

    QLabel *labelQ,
           *labelgamma,
           *labelP,
           *labelX0,
           *labelY0,
           *labelZ0,
           *labelUx0,
           *labelUy0,
           *labelUz0;

    QDoubleSpinBox *doubleSpinBoxQ,
                   *doubleSpinBoxgamma,
                   *doubleSpinBoxP,
                   *doubleSpinBoxX0,
                   *doubleSpinBoxY0,
                   *doubleSpinBoxZ0,
                   *doubleSpinBoxUx0,
                   *doubleSpinBoxUy0,
                   *doubleSpinBoxUz0;

    QPushButton *pushButtonStart,
                *pushButtonStop;
    QTextEdit *textEditLog;

    QTimer *timer;

    Q3DScatter *scatter;
    QScatter3DSeries *series;
    QScatter3DSeries *pointseries;

    QScatterDataArray data;
    QScatterDataArray point;

    QValue3DAxis *Xaxis;
    QValue3DAxis *Yaxis;
    QValue3DAxis *Zaxis;




};
#endif // INTERFACE_H
