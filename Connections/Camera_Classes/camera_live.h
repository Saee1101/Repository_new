#ifndef CAMERA_LIVE_H
#define CAMERA_LIVE_H

#include <QObject>
#include <QThread>
#include <HalconCpp.h>
#include <QtCore>
#include <QDebug>
#include <string>
#include <time.h>
#include <iostream>
#include "HalconCpp.h"
#include "HDevThread.h"
#include <QElapsedTimer>
#include "QMutex"

using namespace HalconCpp;
using namespace std;

class Camera_Live : public QThread
{
    Q_OBJECT
public:
    explicit Camera_Live(QObject *parent = nullptr) ;
    void run();
    bool grabberexistFlag_Live=false;
    void Set_Grabber_name_Live(HFramegrabber *grabber);
    void Close_Frame_Live();
    HFramegrabber* LiveGrabber;
    HImage LiveImage;
    QMutex *mutex;
    int cond_Live=false;

signals:
    void cameraImagesend_Live(HalconCpp::HImage*);

};

#endif // CAMERA_LIVE_H
