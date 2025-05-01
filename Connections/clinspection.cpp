#include "clinspection.h"

QVector<double>results;
CLInspection::CLInspection(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
    : QObject{parent}
{
    Initalization(c,Z,m);

    // AIWorker = new FLAI;
    // AIWorker->topbottonflg = topbottom;
    // AIThread = new QThread(this);
    // AIWorker->moveToThread(AIThread);
    // AIWorker->mutex=&mutex;
    camera->mutex=&mutex;
    eProc = new EdgeProcess("model.json");
}

double CLAIJob(int i,int samplenumber,HImage im, QMutex *mu,EdgeProcess *oProc)
{
    QElapsedTimer tim;
    tim.start();
    Label label;
    QMutex *m=mu;
    double result;
    CarpoolContour mainContour, secondContour;
    HalconCpp::HImage image, croppedImage;
    std::vector<double> features;
    image = im;
    std::tie(result, label, croppedImage, features, mainContour, secondContour) = oProc->predictWithDetails(image, LEFT);
    qDebug()<<i<<"time"<<tim.elapsed();
    m->lock();
    results[i]=result;
    m->unlock();
    return  samplenumber;
}

void CLInspection::Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
{
    Set_Machine_Manager(m);
    Set_CameraParameter(Z);
    Set_Camera_thread(c);
    // myPool.setMaxThreadCount(QThread::idealThreadCount()-5);
    // myPool.setThreadPriority(QThread::HighPriority);
}

void CLInspection::Start()
{
    finishedCount=0;
    imagecounter=0;
    Images.resize(picturecount);
    results.resize(picturecount);
    connect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
            this,SLOT(CameraImageRecived(HalconCpp::HImage*)));
    cameraparameter->Camera_Set_Grabbing_Senario(Camera_Parameter::senario::triggerfreerun);
    camera->cond_Live=true;
    Counting_protecter.start();
    camera->start();
    camera->setPriority(QThread::HighPriority);
    qDebug()<<"clinspectionstart";
    timertest.start();
    samplenumber=0;
}

void CLInspection::Stop()
{
    disconnect(camera, SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),
               this,SLOT(CameraImageRecived(HalconCpp::HImage*)));
    results.fill(1);
    finishedCount=0;
    imagecounter=0;
    camera->cond_Live=false;
    // AIThread->quit();
    // AIThread->wait();
}

void CLInspection::Set_RejectFlag(bool ovalflag)
{
    CLFlag=!ovalflag;
}

void CLInspection::Set_Inspection_Param(double maxoval, double minoval)
{
    MinCL=minoval;
    MaxCL=maxoval;
}


void CLInspection::Set_Machine_Manager(MachineManager *m)
{
    machinemanager = m;
}

void CLInspection::Set_CameraParameter(ZDS_camera_parameter *m)
{
    cameraparameter = m;
}

void CLInspection::Set_Camera_thread(Camera_Live *m)
{
    camera = m ;
}

void CLInspection::Set_PictureCount(int count)
{
    picturecount=count;
}

void CLInspection::FinalDesision()
{

    qDebug() << "All tasks finished!"<<timertest.elapsed();
    auto index = std::min_element(results.constBegin(),results.constEnd());
    finishedCount = 0;
    imagecounter=0;
    int ii= std::distance(results.constBegin(),index);
    if(*index<MinCL && CLFlag){
        machinemanager->machine->jacklist[2]->triggerExecuteOn();
        AcceptFlag=false;
    }
    MinImage=Images[ii];
    MinScore=*index;
    emit CLResultsSend(&MinImage,MinScore,AcceptFlag);
    results.fill(1);
}

void CLInspection::CameraImageRecived(HImage *im)
{
    if(imagecounter==0)
        timertest.restart();

    qDebug()<<"image"<<imagecounter;
    // if(imagecounter==picturecount)
        // imagecounter=0;
    AcceptFlag=true;
    if(Counting_protecter.elapsed()>200 ||imagecounter>=picturecount ){
        imagecounter=0;
        finishedCount=0;
        // samplenumber++;
    }
    Counting_protecter.restart();
    Images[imagecounter]=*im;

    QFutureWatcher<double>* watcher = new QFutureWatcher<double>();
    QObject::connect(watcher, &QFutureWatcher<double>::finished, [&]() {
        // if(watcher->future().result()==samplenumber)
        finishedCount++;
        // watcher->deleteLater();
        // qDebug() << "Watcher detected task finished. Total finished:" << finishedCount;
        if (finishedCount == picturecount) {
            FinalDesision();
        }
    });
    QFuture<double> future = QtConcurrent::run(CLAIJob,samplenumber,imagecounter,*im,&mutexwatcher,eProc);
    imagecounter++;
    watcher->setFuture(future);

}


// void CLInspection::onAIResultSend(HalconCpp::HImage* im,double min,double max)
// {
//     AcceptFlag=true;
//     if(OvalFlag)
//         if(min*PixToMM_min<Minoval || max*PixToMM_max>Maxoval){
//             machinemanager->machine->jacklist.at(AIWorker->topbottonflg)->triggerExecuteOn();
//             AcceptFlag=false;
//         }

//     emit Inspection_Result_Send(im, min*PixToMM_min,max*PixToMM_max,AcceptFlag,AIWorker->topbottonflg);

// }

