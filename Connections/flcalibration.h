#ifndef FLCALIBRATION_H
#define FLCALIBRATION_H

#include <QObject>
#include "Camera_Classes/camera_live.h"
#include"machinemanager.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "flai.h"
#include "QThread"
#include "QMutex"
class FLCalibration : public QObject
{
    Q_OBJECT
public:
    explicit FLCalibration(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m,bool topbottom);
    void Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Start();
    void Stop();
    void Get_Result();
    void Set_PIX_MM(double minpix2mmm,double maxpix2mm);
    void Set_Machine_Manager(MachineManager* m);
    void Set_CameraParameter(ZDS_camera_parameter* m);
    void Set_Camera_thread(Camera_Live* m );
    void SetNewDiameters(double min,double max);
    void get_PIX_MM(double* minpix2mmm,double*maxpix2mm);
    MachineManager *machinemanager;
    Camera_Live *camera;
    ZDS_camera_parameter *cameraparameter;
    FLAI *AIWorker;
    double MinDiameter,MaxDiameter;
    QThread *AIThread;
    QMutex mutex;
    double PixToMM_min,PixToMM_max,Maxoval,Minoval;
signals:
    void Calibration_Result_Send(HalconCpp::HImage* im,double min ,double max,int Station);
public slots:
    void onAIResultSend(HalconCpp::HImage* im ,double min ,double max);
};

#endif // FLCALIBRATION_H
