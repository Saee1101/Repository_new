#include "Business_logic.h"

Business_logic::Business_logic(QObject *parent)
    : QObject{parent}
    , entities(QSqlDatabase::database())
// ,CRUD_machine_setting_db("machine_setting")
// ,CRUD_sample_db("sample")
// ,CRUD_user_db("user")
// ,CRUD_user_role_db("user_role")
{

}

void Business_logic::System_Set_Mode(int Mode)
{
    entities.loadData();
    switch (Mode) {
    case Mode::Inspection:
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Inpection_Result(HalconCpp::HImage*,double,double,bool,int))
                ,this,SLOT(ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage*,double,double,bool,int)));

        connect(&connectionlayer,SIGNAL(connectionLayer_CL_Inpection_Result(HalconCpp::HImage*,double,bool))
                ,this,SLOT(ConnectionLayer_CL_Inpection_Result_Recived(HalconCpp::HImage*,double,bool)));

        connectionlayer.Inspection_Start(&entities.dataMap_sample_db,&entities.dataMap_machine_setting_db);
        break;
    case Mode::FL1Calibration:
        //connections
        qDebug()<<"fl1newmmin"<<Fl1_Min_Diameter<<"fl1max"<<Fl1_Max_Diameter;
        connectionlayer.Calibration_Start(Connections::Stations::FL1,Fl1_Min_Diameter,Fl1_Max_Diameter);
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double,double,int))
                ,this,SLOT(ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double,int)));
        break;
    case Mode::FL2Calibration:
        //connections
        connectionlayer.Calibration_Start(Connections::Stations::FL2,Fl2_Min_Diameter,Fl2_Max_Diameter);
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double,double,int))
                ,this,SLOT(ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double,int)));
        break;
    case Mode::FL1setting:
        //connections;
        connectionlayer.Machie_Run(MachineManager::senario::Inspection);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::FL1,Connections::CameraGrabMode::Trigger,true);
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*))
                ,this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        break;
    case Mode::FL2setting:
        //connections;
        connectionlayer.Machie_Run(MachineManager::senario::Inspection);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::FL2,Connections::CameraGrabMode::Trigger,true);
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*))
                ,this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        break;
    case Mode::CLsetting:
        //connections;
        connectionlayer.Machie_Run(MachineManager::senario::Inspection);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::CL,Connections::CameraGrabMode::Trigger,true);
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*))
                ,this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        break;
    case Mode::systemOff:
        connectionlayer.Machie_Run(MachineManager::senario::systemOff);
        //disconnections
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Inpection_Result(HalconCpp::HImage*,double,double,bool,int))
                   ,this,SLOT(ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage*,double,double,bool,int)));
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double,double,int))
                   ,this,SLOT(ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double,int)));
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*))
                   ,this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        disconnect(&connectionlayer,SIGNAL(connectionLayer_CL_Inpection_Result(HalconCpp::HImage*,double,bool))
                   ,this,SLOT(ConnectionLayer_CL_Inpection_Result_Recived(HalconCpp::HImage*,double,bool)));
        connectionlayer.Inspection_Stop();
        connectionlayer.Calibration_Stop(Connections::Stations::FL1);
        connectionlayer.Calibration_Stop(Connections::Stations::FL2);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::FL1,Connections::CameraGrabMode::Trigger,false);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::FL2,Connections::CameraGrabMode::Trigger,false);
        connectionlayer.Camera_Start_Grabbing_Setting(Connections::Stations::CL,Connections::CameraGrabMode::Trigger,false);
        break;
    }
}

void Business_logic::CheckSystem_Connection_Status()
{
    entities.loadData();


//     bool plcconnection_flg=connectionlayer.Check_Plc();
//     if(plcconnection_flg){
//         connectionlayer.Check_Camera();
//         if(connectionlayer.Camera_Connection_Flag.contains(false))
//         emit BusinessLogic_Camera_Connection_Status(connectionlayer.Camera_Connection_Flag.at(0),
//                                                     connectionlayer.Camera_Connection_Flag.at(1),
//                                                     connectionlayer.Camera_Connection_Flag.at(2));
//         else
//             Initial_System();
// }
//     else{
//         emit BusinessLogic_PLC_Connection_Status(false);
// }


}

void Business_logic::Initial_System()
{

    connectionlayer.Machin_init(&entities.dataMap_machine_setting_db);
    connectionlayer.camera_init(&entities.dataMap_machine_setting_db);
    connectionlayer.IspectionInit();
    connectionlayer.CalibrationInit();
    connectionlayer.Machie_Run(MachineManager::senario::systemOff);

}

void Business_logic::Change_Pix_To_Mm(double new_min, double new_max,int station)
{
    if(station){
        Fl1_Max_Diameter=new_max;
        Fl1_Min_Diameter=new_min;
    }else{
        Fl2_Max_Diameter=new_max;
        Fl2_Min_Diameter=new_min;
    }
}

void Business_logic::ConnectionLayer_Inpection_Result_Recived(HImage *im, double minoval, double maxoval, bool AcceptFlag, int station)
{
    emit BusinessLogic_Inpection_Result(im, minoval,maxoval,AcceptFlag,station);
}

void Business_logic::ConnectionLayer_Calibration_Result_Recived(HImage *im, double minoval, double maxoval, int station)
{
    emit BusinessLogic_Calibration_Result(im, minoval,maxoval,station);
}

void Business_logic::ConnectionLayer_Setting_Camera_Recived(HImage *im)
{
    emit BusinessLogic_Setting_Camera_Result(im);
}

void Business_logic::ConnectionLayer_CL_Inpection_Result_Recived(HImage *im, double score, bool AcceptFlag)
{
    emit BusinessLogic_CL_Inpection_Result(im, score,AcceptFlag);

}

