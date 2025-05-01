#ifndef HALCONQTWINDOW_H
#define HALCONQTWINDOW_H

#include <QWidget>
#include "HalconCpp.h"
class halconqtwindow : public QWidget
{
    Q_OBJECT
public:
    explicit halconqtwindow(QWidget *parent = nullptr,long Width=0,long Height=0);
    void openwindow(int ,int);
  //  HalconCpp::HTuple WindID;
    HalconCpp::HWindow Wind;
    HalconCpp::HWindow WinfoeID(void) {return Wind;}

signals:

};

#endif // HALCONQTWINDOW_H
