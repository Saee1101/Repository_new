#include "flcalibration.h"


FLCalibration::FLCalibration(QObject *parent, Camera_Live *c, ZDS_camera_parameter *Z, MachineManager *m, bool topbottom)
{
    Initalization(c,Z,m);
    AIWorker = new FLAI;
    AIWorker->topbottonflg = topbottom;
    AIThread = new QThread(this);
    AIWorker->moveToThread(AIThread);
}

void FLCalibration::Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
{
    Set_Machine_Manager(m);
    Set_CameraParameter(Z);
    Set_Camera_thread(c);
}

void FLCalibration::Start()
{
    // AIWorker->mutex=&mutex;
    // camera->mutex = &mutex;
    qDebug()<<"fl2started";
    connect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
            AIWorker,SLOT(getImage(HalconCpp::HImage*)), Qt::QueuedConnection);
    connect(AIWorker,SIGNAL(sendresults(HalconCpp::HImage*,double,double)),this,SLOT(onAIResultSend(HalconCpp::HImage*,double,double)));
    cameraparameter->Camera_Set_Grabbing_Senario(Camera_Parameter::senario::triggerfreerun);
    camera->cond_Live=true;
    camera->start();
    AIThread->start();
    // AIThread->setPriority(QThread::HighPriority);
    // camera->setPriority(QThread::HighPriority);
}
void FLCalibration::Set_Machine_Manager(MachineManager *m)
{
    machinemanager = m;
}

void FLCalibration::Set_CameraParameter(ZDS_camera_parameter *m)
{
    cameraparameter = m;
}

void FLCalibration::Set_Camera_thread(Camera_Live *m)
{
    camera = m ;
}
void FLCalibration::Stop()
{
    disconnect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
               AIWorker,SLOT(getImage(HalconCpp::HImage*)));
    disconnect(AIWorker,SIGNAL(sendresults(HalconCpp::HImage*,double,double)),this,SLOT(onAIResultSend(HalconCpp::HImage*,double,double)));
    camera->cond_Live=false;
    AIThread->quit();
    AIThread->wait();
}

void FLCalibration::Set_PIX_MM(double minpix2mmm, double maxpix2mm)
{
    PixToMM_max=maxpix2mm;
    PixToMM_min=minpix2mmm;
    qInfo()<<"calibPixToMM_min-max"<<minpix2mmm<<" "<<maxpix2mm;
}

void FLCalibration::SetNewDiameters(double min, double max)
{
    MinDiameter=min;
    MaxDiameter=max;
}

void FLCalibration::get_PIX_MM(double *minpix2mm, double *maxpix2mm)
{
    *minpix2mm=PixToMM_min;
    *maxpix2mm=PixToMM_max;
}

void FLCalibration::onAIResultSend(HImage *im, double min, double max)
{
    if(min>10&& max>10){
        Stop();
        PixToMM_min   = MinDiameter/min;
        PixToMM_max   = MaxDiameter/max;
        qDebug()<<"newmin"<<MinDiameter<<"newmax"<<MaxDiameter;
        qDebug()<<"minlog"<<min<<"maxlog"<<max;

         Calibration_Result_Send(im,min,max,AIWorker->topbottonflg);
    }
}

