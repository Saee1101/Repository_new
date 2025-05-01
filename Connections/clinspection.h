#ifndef CLINSPECTION_H
#define CLINSPECTION_H

#include <QObject>
#include "Camera_Classes/camera_live.h"
#include"machinemanager.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "QThread"
#include "QMutex"
#include "EdgeProcess.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QElapsedTimer>
class CLInspection : public QObject
{
    Q_OBJECT
public:
    explicit CLInspection(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Start();
    void Stop();
    void Get_Result();
    void Set_RejectFlag(bool flag);
    void Set_Inspection_Param(double max,double min);
    void Set_Machine_Manager(MachineManager* m);
    void Set_CameraParameter(ZDS_camera_parameter* m);
    void Set_Camera_thread(Camera_Live* m );
    void Set_PictureCount(int count);
    void FinalDesision();
    int finishedCount,imagecounter;
    MachineManager *machinemanager;
    EdgeProcess *eProc;
    Camera_Live *camera;
    HImage MinImage;
    double MinScore;
    ZDS_camera_parameter *cameraparameter;
    QMutex mutex ,mutexwatcher;
     QThreadPool myPool;
    QElapsedTimer Counting_protecter, timertest;
    QVector<HImage>Images;
    int picturecount;
    bool CLFlag;
    double MaxCL,MinCL;
    bool AcceptFlag;
   int samplenumber;

signals:
    void CLResultsSend(HImage* im , double score,bool result);
public slots:
    void CameraImageRecived(HImage* im);
};

#endif // CLINSPECTION_H
