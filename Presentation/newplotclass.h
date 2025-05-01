#ifndef NEWPLOTCLASS_H
#define NEWPLOTCLASS_H
#include "qcustomplot.h"
#include <QWidget>

class newplotclass : public QWidget
{
    Q_OBJECT
public:
    explicit newplotclass(QWidget *parent = nullptr);
void setparameter(double WindowsWidth, double WindowsHight,double Xrang,double Yrange,
                  double main_value,double up_telorance,double low_telorance);
void setData(double data);
bool statusData();
double Up_tel,Lo_tel,Nominal;
//    void setparameter(double axis);
signals:
private:
    QCustomPlot *customPlot;
    QCPItemText* textLable[20];
    QVector<double>  vec_y ,vec_y_r;
    QVector<double> vec_x, vec_x_r;


    int postcounter;
    bool status;

};

#endif // NEWPLOTCLASS_H
