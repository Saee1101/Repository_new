#include "flinspection.h"


FLInspection::FLInspection(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m,bool topbottom)
    : QObject{parent}
{
    Initalization(c,Z,m);
    AIWorker = new FLAI;
    AIWorker->topbottonflg = topbottom;
    AIThread = new QThread(this);
    AIWorker->moveToThread(AIThread);
}

void FLInspection::Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
{
    Set_Machine_Manager(m);
    Set_CameraParameter(Z);
    Set_Camera_thread(c);
}

void FLInspection::Start()
{
    // AIWorker->mutex=&mutex;
    // camera->mutex=&mutex;
    connect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
            AIWorker,SLOT(getImage(HalconCpp::HImage*)), Qt::QueuedConnection);
    connect(AIWorker,SIGNAL(sendresults(HalconCpp::HImage*,double,double)),this,SLOT(onAIResultSend(HalconCpp::HImage*,double,double)));
    cameraparameter->Camera_Set_Grabbing_Senario(Camera_Parameter::senario::triggerfreerun);
    camera->cond_Live=true;
    camera->start();
    AIThread->start();
    AIThread->setPriority(QThread::HighPriority);
    camera->setPriority(QThread::HighPriority);
    qDebug()<<"inspectionstart";
}

void FLInspection::Stop()
{
    disconnect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
            AIWorker,SLOT(getImage(HalconCpp::HImage*)));
    disconnect(AIWorker,SIGNAL(sendresults(HalconCpp::HImage*,double,double)),this,SLOT(onAIResultSend(HalconCpp::HImage*,double,double)));
    camera->cond_Live=false;
    AIThread->quit();
    AIThread->wait();
}

void FLInspection::Set_RejectFlag(bool ovalflag)
{
    OvalFlag=!ovalflag;
    qInfo()<<"OvalFlag"<<OvalFlag;
}

void FLInspection::Set_Inspection_Param(double maxoval, double minoval)
{
    Minoval=minoval;
    Maxoval=maxoval;
    qInfo()<<"min-max"<<Minoval<<" "<<Maxoval;
}

void FLInspection::Set_PIX_MM(double minpix2mmm, double maxpix2mm)
{
    PixToMM_max=maxpix2mm;
    PixToMM_min=minpix2mmm;
    qInfo()<<"PixToMM_min-max"<<minpix2mmm<<" "<<maxpix2mm;
}

void FLInspection::Set_Machine_Manager(MachineManager *m)
{
    machinemanager = m;
}

void FLInspection::Set_CameraParameter(ZDS_camera_parameter *m)
{
    cameraparameter = m;
}

void FLInspection::Set_Camera_thread(Camera_Live *m)
{
    camera = m ;
}


void FLInspection::onAIResultSend(HalconCpp::HImage* im,double min,double max)
{

    AcceptFlag=true;

        if(min*PixToMM_min<Minoval || max*PixToMM_max>Maxoval){
            if(OvalFlag)
            machinemanager->machine->jacklist.at(AIWorker->topbottonflg)->triggerExecuteOn();
            AcceptFlag=false;
        }
         resultimage=*im;
      emit Inspection_Result_Send(&resultimage, min*PixToMM_min,max*PixToMM_max,true,AIWorker->topbottonflg);
        // emit Inspection_Result_Send(im, 3.10,4.45,AcceptFlag,AIWorker->topbottonflg);


}
