#ifndef FLAI_H
#define FLAI_H

#include <QObject>
#include "HalconCpp.h"
#include "HDevThread.h"
#include "vector"
#include <QVector>
#include "fl1fl2ai/HelperClass.h"
#include "fl1fl2ai/TopDiameter.h"
#include "fl1fl2ai/BottomDiameter.h"
#include "QSharedPointer"
#include "QMutex"
using namespace HalconCpp;
using namespace std;
class FLAI : public QObject
{
    Q_OBJECT
public:
    explicit FLAI(QObject *parent = nullptr);
    OvalityMeasures oval;
    HelperClass circleDiameter;
    TopDiameter topDiameter;
    BottomDiameter bottomDiameter;
    HImage resultImage,InputImage;
    bool topbottonflg;
    QMutex *mutex;
public slots:
    void getImage(HalconCpp::HImage* rawImage);
signals:
    void sendresults(HalconCpp::HImage* proccesImage,double min,double max);
};

#endif // FLAI_H
