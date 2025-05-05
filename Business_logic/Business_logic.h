#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H
#define DllImport   __declspec( dllimport )
#include "Business_logic_global.h"
#include "Entities.h"
#include "Connections.h"
#include <QObject>
#include <QScopedPointer>


class  Business_logic:public QObject
{
    Q_OBJECT
public:
    DllImport  explicit Business_logic(QObject *parent = nullptr);


QSqlDatabase business_db;

    Connections connectionlayer;
    Entities entities;

    DllImport void System_Set_Mode(int Mode);
    DllImport void CheckSystem_Connection_Status();
    DllImport void Initial_System();
    DllImport void PlcConnection();
    DllImport void PlcDisconnection();
    DllImport bool CameraReconnection();
    DllImport void CameraDisconnection();
    DllImport static Business_logic *getInstance();
    struct Mode {
        static const int Inspection=0;
        static const int FL1Calibration=1;
        static const int FL2Calibration=2;
        static const int systemOff=3;
        static const int FL1setting = 4;
        static const int FL2setting = 5;
        static const int CLsetting = 6;
    };
    DllImport void Check_Status(QVector<double> *machine_status);
    DllImport void Change_Pix_To_Mm(double new_min, double new_max,int station);
    double Fl1_Min_Diameter,Fl1_Max_Diameter,Fl2_Min_Diameter,Fl2_Max_Diameter;
    bool Setting_Save_Image_Flag;
    int Setting_count_Image_Save=0;
    DllImport void Report_db();
    /////////////////////////////////
    // DllImport void push_map ();
public slots:
    void ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage* im,double minoval,
                                                  double maxoval,bool AcceptFlag,int station);
    void ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage* im,double minoval ,double maxoval,int station);

    void ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*im);
    void ConnectionLayer_CL_Inpection_Result_Recived(HalconCpp::HImage *im,double score,bool AcceptFlag);

    signals:
    void BusinessLogic_Inpection_Result(HalconCpp::HImage* im,double minoval,
                                            double maxoval,bool AcceptFlag,int station);
    void BusinessLogic_Calibration_Result(HalconCpp::HImage* im,double minoval ,double maxoval,int station);

     void BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*im);
    void BusinessLogic_Camera_Connection_Status(bool fl1,bool fl2,bool cl);
     void BusinessLogic_PLC_Connection_Status(bool c);
    void BusinessLogic_CL_Inpection_Result(HalconCpp::HImage* im,double score ,bool flag);
};

#endif // BUSINESS_LOGIC_H
