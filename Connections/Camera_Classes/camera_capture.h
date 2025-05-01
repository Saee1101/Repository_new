#ifndef CAMERA_CAPTURE_H
#define CAMERA_CAPTURE_H

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
using namespace HalconCpp;

class Camera_Capture : public QThread
{
    Q_OBJECT
public:
    explicit Camera_Capture(QObject *parent = nullptr);
    void run();
    void Set_Grabber_name_Capture(HFramegrabber *grabber);
    HFramegrabber *CaptureGrabber;
    bool grabberexistFlag_Capture=false;
    void Close_Frame_Capture();
    HImage CaptureImage;
    HImage imageread;
    int cond_Capture;
    bool Save_or_Not;
    int captured_Count;
    int Picture_Count;



signals:
    void cameraImagesend_Capture(HalconCpp::HImage*);


};

#endif // CAMERA_CAPTURE_H
