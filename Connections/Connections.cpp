#include "Connections.h"

Connections::Connections(QObject *parent)
    : QObject{parent}
{
    plcmodbusconnect_ = new plcmodbusconnect(this);
}

void Connections::Inspection_Start(QMap<QString, QString> *samplemap,QMap<QString, QString> *machinmap)
{
    savenumber=0;
    Machie_Run(MachineManager::senario::Inspection);
    for(int i=0;i<2;i++)
        if(Camera_Connection_Flag.at(i)){
            IspectionUpdate(samplemap,machinmap,i);
            FLInspection_List[i]->Start();

        }
    if(Camera_Connection_Flag.at(2)){
        IspectionUpdate(samplemap,machinmap,2);
        CLInspection_->Start();
    }
}

void Connections::Inspection_Stop()
{
    Machie_Run(MachineManager::senario::systemOff);
    for(int i=0;i<2;i++)
        if(Camera_Connection_Flag.at(i))
            FLInspection_List[i]->Stop();
    if(Camera_Connection_Flag.at(2))
        CLInspection_->Stop();
}

void Connections::Calibration_Start(int Station,double NewMinDiameter,double NewMaxDiameter)
{
    Machie_Run(MachineManager::senario::Inspection);
    if(Camera_Connection_Flag.at(Station)){
        FLCalibration_List[Station]->SetNewDiameters(NewMinDiameter,NewMaxDiameter);
            FLCalibration_List[Station]->Start();
    }
}

void Connections::Calibration_Stop(int Station)
{
    Machie_Run(MachineManager::senario::systemOff);
    if(Camera_Connection_Flag.at(Station))
        FLCalibration_List[Station]->Stop();
    //disconnections
    //set Pix to MM to DB
}

bool Connections::Check_Plc()
{
    qDebug()<<"here??";
    plcmodbusconnect_->PlcConnectionConfigFromJson("plcconnectionconfig.json");
    if(plcmodbusconnect_->PlcConnectionInit())
    {
        return true;
    }
    else{
        qDebug()<<"Connections::Check_Plc failed !!";
        // emit failed_connects_C("PLC IS NOT CONNECTED .");
        return false;
    }
    // }else
    //     return true;
}

void Connections::Check_Camera()
{
    QStringList cameralist;
        Available_Cameras_ = new Available_Cameras(this);
    Available_Cameras_->Read_Station_Camera_From_Json("CamerasStation.json");
        Available_Cameras_->cam_name_sender(&cameralist);
        Camera_Connection_Flag.resize(3);
        Camera_Connection_Flag[Stations::FL1]=cameralist.contains(Available_Cameras_->RegisteredCameraName.at(Stations::FL1));
        Camera_Connection_Flag[Stations::FL2]=cameralist.contains(Available_Cameras_->RegisteredCameraName.at(Stations::FL2));
        Camera_Connection_Flag[Stations::CL]=cameralist.contains(Available_Cameras_->RegisteredCameraName.at(Stations::CL));
}

void Connections::camera_init(QMap<QString, QString> *map)
{
    ZDS_camera_parameter_List.resize(3);
    Camera_Live_List.resize(3);
    bool ok =true;
    for(int i=0;i<3;i++){
    if(Camera_Connection_Flag.at(i)){
    ZDS_camera_parameter_List[i] = new ZDS_camera_parameter(this);
    Camera_Live_List[i] = new Camera_Live (this);
    ZDS_camera_parameter_List[i]->SetPlcModbusRW(plcmodbusRW_);
    ZDS_camera_parameter_List[i]->Camera_Construction(Available_Cameras_->RegisteredCameraName.at(i));
    Camera_Live_List[i]->Set_Grabber_name_Live(ZDS_camera_parameter_List[i]->Camera_Get_Grabber());
    ZDS_camera_parameter_List[i]->Camera_Trigger_Input_Delay_Address(map->value("Trigger_Input_Delay_Address_fl"+QString::number(i+1)).toInt(&ok,16));
    ZDS_camera_parameter_List[i]->Camera_Set_Delay(map->value("Delay_fl"+QString::number(i+1)).toInt());
    ZDS_camera_parameter_List[i]->Camera_Set_Exposure(map->value("Exposure_fl"+QString::number(i+1)).toInt());
    ZDS_camera_parameter_List[i]->Camera_Set_ROI(map->value("XOffset_fl"+QString::number(i+1)).toInt(),
                                          map->value("YOffset_fl"+QString::number(i+1)).toInt(),
                                          map->value("Width_fl"+QString::number(i+1)).toInt(),
                                          map->value("Height_fl"+QString::number(i+1)).toInt());
    ZDS_camera_parameter_List[i]->Camera_Set_FrameRate(map->value("FrameRate_fl"+QString::number(i+1)).toInt());
    // ZDS_camera_parameter_List[i]->Camera_Set_Grabbing_Mode(ZDS_camera_parameter::CommandType::hardware);
    ZDS_camera_parameter_List[i]->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::triggerfreerun);
    // Camera_Live_List[i]->setPriority(QThread::HighPriority);
    if(i==2){
        ZDS_camera_parameter_List[i]->Camera_Burst_Mode_Enable(true,map->value("picture_count_cl").toInt());
    }
    }
}
}

bool Connections::Machin_init(QMap<QString, QString> *map)
{
    plcmodbusRW_ =new plcmodbusRW(this,plcmodbusconnect_->getdevice());
    // plcmodbusRW_->WriteCoil(0x80e,true);
    Machine_=new Machine(this,plcmodbusRW_);
    machinesetting_=new MachineSetting_con(this,Machine_);
    MachineManager_=new MachineManager(this,Machine_);
    Machine_->setMachineMap(4,0);
    qDebug()<<"13";
    QStringList jackjasonlist,motorjsonlist;
    jackjasonlist.append("jack1config.json");
    jackjasonlist.append("jack2config.json");
    jackjasonlist.append("jack3config.json");
    jackjasonlist.append("jack4config.json");
    qDebug()<<"15";
    Machine_->ReadMachineConfigFromJson(jackjasonlist,motorjsonlist);
    qDebug()<<"17";
    machinesetting_->UpdateJackSetting(0,map->value("lift_delay_fl").toDouble(),
                                       map->value("lift_time_fl").toDouble());
    machinesetting_->UpdateJackSetting(1,map->value("lift_delay_fl").toDouble(),
                                       map->value("lift_time_fl").toDouble());
    machinesetting_->UpdateJackSetting(2,map->value("lift_delay_cl").toDouble(),
                                       map->value("lift_time_cl").toDouble());
    machinesetting_->UpdateJackSetting(3,map->value("reject_delay").toDouble(),
                                       map->value("reject_time").toDouble());
    qDebug()<<"166";
    MachineManager_->SetMachineSenario(MachineManager::senario::systemOff);
    qDebug()<<"16";
    MachineManager_->setrejectjack(3);
    return true;
}

void Connections::IspectionInit()
{
    FLInspection_List.resize(2);
    for (int i=0;i<2;i++){
        qDebug()<<"inspectionstart,,,,,\\\\\///////////////////////////////";
        if(Camera_Connection_Flag.at(i)){
            FLInspection_List[i]=new FLInspection(this,Camera_Live_List.at(i),ZDS_camera_parameter_List.at(i),MachineManager_,i);
        connect(FLInspection_List[i],SIGNAL(Inspection_Result_Send(
                                 HalconCpp::HImage*,double,double,bool,int))
                ,this,SLOT(Inpection_Result_Recived(HalconCpp::HImage*,double,double,bool,int)));
        }
    }
    if(Camera_Connection_Flag.at(2)){
        CLInspection_ = new CLInspection(this,Camera_Live_List.at(2),ZDS_camera_parameter_List.at(2),MachineManager_);
    connect(CLInspection_,SIGNAL(CLResultsSend(
                                      HalconCpp::HImage*,double,bool))
            ,this,SLOT(CL_Inspection_Result_Recived(HalconCpp::HImage*,double,bool)));
    }
}

void Connections::CalibrationInit()
{
    FLCalibration_List.resize(2);
    for (int i=0;i<2;i++){
        if(Camera_Connection_Flag.at(i)){
            FLCalibration_List[i]=new FLCalibration(this,Camera_Live_List.at(i),ZDS_camera_parameter_List.at(i),MachineManager_,i);
        connect(FLCalibration_List[i],SIGNAL(Calibration_Result_Send(
                                 HalconCpp::HImage*,double,double,int))
                ,this,SLOT(Calibration_Result_Recived(HalconCpp::HImage*,double,double,int)));
        }
    }

}

void Connections::IspectionUpdate(QMap<QString, QString> *samplemap,QMap<QString, QString> *machinmap,int station)
{
    if(station<2){
        FLInspection_List[station]->Set_Inspection_Param(samplemap->value("diamiter_max_fl"+QString::number(station+1)).toDouble(),samplemap->value("diamiter_min_fl"+QString::number(station+1)).toDouble());
        FLInspection_List[station]->Set_RejectFlag((machinmap->value("fl"+QString::number(station+1)+"_reject_status")).toInt());
        FLInspection_List[station]->Set_PIX_MM(machinmap->value("pixel_to_mm_min_fl"+QString::number(station+1)).toDouble(),machinmap->value("pixel_to_mm_max_fl"+QString::number(station+1)).toDouble());
    }
    else{
        CLInspection_->Set_Inspection_Param(machinmap->value("cl_stage").toDouble(),0);
        CLInspection_->Set_PictureCount(machinmap->value("picture_count_cl").toInt());
        CLInspection_->Set_RejectFlag(machinmap->value("cl_reject_status").toInt());
    }
}


void Connections::CalibrationUpdate(QMap<QString, QString> *map,int station)
{
    FLCalibration_List[station]->Set_PIX_MM(map->value("pixel_to_mm_min_fl"+QString::number(station+1)).toDouble(),map->value("pixel_to_mm_max_fl"+QString::number(station+1)).toDouble());
}

void Connections::MotorTest(int item, double speed, int direction, bool ONOFF)
{
    if(ONOFF){
        machinesetting_->UpdateMotorSetting(item,speed);
        Machine_->motorlist.at(item)->JogOn(direction);
    }
    else{
        Machine_->motorlist.at(item)->JogOff();
    }
}

void Connections::JackTest(int item, double delaySetting, double TimeDur, int JacktestMode, bool ONOFF)
{
    if(ONOFF){
        machinesetting_->UpdateJackSetting(item,delaySetting,TimeDur);
        switch (JacktestMode) {
        case JacktestMode::Jog:
            Machine_->jacklist.at(item)->JogOn();
            break;
        case JacktestMode::Cycle:
            Machine_->jacklist.at(item)->CycleExecuteOn();
            break;
        case JacktestMode::Trigger:
            Machine_->jacklist.at(item)->triggerExecuteOn();
            break;
        }}else{
        Machine_->jacklist.at(item)->CycleExecuteOff();
        Machine_->jacklist.at(item)->triggerExecuteOff();
        Machine_->jacklist.at(item)->JogOff();
    }
}
void Connections::Camera_Start_Grabbing_Setting(int cameranumber,int cameraGrabMode, bool ONOFF)
{
    if(Camera_Connection_Flag.at(cameranumber))
    {
    if(ONOFF){
        if(cameraGrabMode==CameraGrabMode::Live){
             ZDS_camera_parameter_List[cameranumber]->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::softwarefreerun);
        }else if(cameraGrabMode==CameraGrabMode::Trigger){
             ZDS_camera_parameter_List[cameranumber]->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::triggerfreerun);
        }
        connect(Camera_Live_List[cameranumber],SIGNAL(cameraImagesend_Live(HalconCpp::HImage*))
                ,this,SLOT(Connection_SettingPreview(HalconCpp::HImage*)));
        qDebug()<<"settinmg start live................";
        Camera_Live_List[cameranumber]->Set_Grabber_name_Live(ZDS_camera_parameter_List[cameranumber]->Camera_Get_Grabber());
        Camera_Live_List[cameranumber]->cond_Live=true;
        Camera_Live_List[cameranumber]->start();
        // Camera_Live_List[cameranumber]->setPriority(QThread::HighPriority);
    }else{
        disconnect(Camera_Live_List[cameranumber],SIGNAL(cameraImagesend_Live(HalconCpp::HImage*))
                   ,this,SLOT(Connection_SettingPreview(HalconCpp::HImage*)));
        Camera_Live_List[cameranumber]->cond_Live=false;
    }
    }
}

void Connections::Camera_Exposure_Setting(int cameranumber,double exposure)
{
    if(Camera_Connection_Flag.at(cameranumber))
     ZDS_camera_parameter_List[cameranumber]->Camera_Set_Exposure(exposure);
}

void Connections::Camera_Delay_Setting(int cameranumber,double delay)
{
    if(Camera_Connection_Flag.at(cameranumber))
     ZDS_camera_parameter_List[cameranumber]->Camera_Set_Delay(delay);
}

void Connections::Camera_ROI_Setting(int cameranumber,double width, double height, double xoffset, double yoffset)
{
    if(Camera_Connection_Flag.at(cameranumber))
    if(Camera_Live_List[cameranumber]->cond_Live==false){
        ZDS_camera_parameter_List[cameranumber]->grabber->Clear();
        ZDS_camera_parameter_List[cameranumber]->Camera_Construction(Available_Cameras_->RegisteredCameraName.at(cameranumber));
        ZDS_camera_parameter_List[cameranumber]->Camera_Set_ROI(xoffset,yoffset,width,height);
        Camera_Live_List[cameranumber]->Set_Grabber_name_Live(ZDS_camera_parameter_List[cameranumber]->Camera_Get_Grabber());
    }
}

void Connections::Camera_FRMRate_Setting(int cameranumber, double framerate)
{
    if(Camera_Connection_Flag.at(cameranumber))
        ZDS_camera_parameter_List[cameranumber]->Camera_Set_FrameRate(framerate);
}

void Connections::Camera_Burst_Setting(int cameranumber, double picnumber)
{
    if(Camera_Connection_Flag.at(cameranumber))
        ZDS_camera_parameter_List[cameranumber]->Camera_Burst_Mode_Enable(true,picnumber);
}

void Connections::Machie_Run(int mashine_senario)
{
    MachineManager_->SetMachineSenario(mashine_senario);
}

void Connections::UpdatePixmap(double New_Min_Pix_To_Mm, double New_Max_Pix_To_Mm)
{
    newmin=New_Min_Pix_To_Mm;
    newmax=New_Max_Pix_To_Mm;
}

void Connections::Inpection_Result_Recived(HImage *im, double minoval, double maxoval, bool AcceptFlag,int station)
{
     qDebug()<<station<<"inpectionrecived"<<minoval<<" "<<AcceptFlag;
    emit ConnectionLayer_Inpection_Result(im,minoval,maxoval,AcceptFlag,station);
     if(AcceptFlag){
        if(savenumber>100)
             savenumber=0;
        savenumber++;
         QString name="fl"+QString::number(station+1)+QString::number(savenumber);
        im->WriteImage("tiff",0,name.toStdString().c_str());
     }

}

void Connections::Calibration_Result_Recived(HImage *im, double minoval, double maxoval,int station)

{
    qDebug()<<"inconnectionmin"<<minoval<<"andmax"<<maxoval;
    emit ConnectionLayer_Calibration_Result(im,minoval,maxoval,station);
}

void Connections::Connection_SettingPreview(HImage *im)
{
    emit ConnectionLayer_Setting_Result(im);
}

void Connections::CL_Inspection_Result_Recived(HImage *im, double score, bool AcceptFlag)
{
 emit connectionLayer_CL_Inpection_Result(im,score,AcceptFlag);
}
