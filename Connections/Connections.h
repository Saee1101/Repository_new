


#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#define DllImport   __declspec( dllimport )

#include "Connections_global.h"
#include "machine.h"
#include "machinemanager.h"
#include "machinesetting.h"
#include "Camera_Classes/available_cameras.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "Camera_Classes/camera_live.h"
#include <QObject>
#include "flinspection.h"
#include "flcalibration.h"
#include "clinspection.h"
class plcmodbusconnect;
class plcmodbusRW;
class Machine;
class MachineSetting_con;
class MachineManager;
class Available_Cameras;
class ZDS_camera_parameter;
class Camera_Live;
class FLInspection;
class FLCalibration;
class CLInspection;
class  Connections : public QObject
{
    Q_OBJECT
public:
 DllImport explicit Connections(QObject *parent = nullptr);
    DllImport void Inspection_Start(QVariantMap *samplemap,QVariantMap *machinmap);
    DllImport void Inspection_Stop();
    DllImport void Calibration_Start(int Station,double NewMinDiameter,double NewMaxDiameter);
    DllImport void Calibration_Stop(int Station);
    DllImport  bool Check_Plc();
    DllImport  void Disconnect_Plc();
    DllImport  bool Reconnect_Plc();
    DllImport  void Check_Camera();
    DllImport  void Disconnect_Camera();
    DllImport  bool Reconnect_Camera(int cameracount);
    DllImport  void camera_init(QVariantMap *map);
    DllImport  bool Machin_init(QVariantMap *map);
    DllImport void IspectionInit();
    DllImport void CalibrationInit();
    DllImport void IspectionUpdate(QVariantMap *samplemap,QVariantMap *machinmap,int station);
    DllImport void CalibrationUpdate(QVariantMap *map,int station);
    DllImport void MotorTest(int item,double speed,int direction,bool ONOFF);
    DllImport void JackTest(int item,double delaySetting,double TimeDur,int JacktestMode,bool ONOFF);
    DllImport void Camera_Start_Grabbing_Setting(int cameranumber,int cameraGrabMode,bool ONOFF);
    DllImport void Camera_Exposure_Setting(int cameranumber,double exposure);
    DllImport void Camera_Delay_Setting(int cameranumber,double delay);
    DllImport void Camera_ROI_Setting(int cameranumber,double width,double height,double xoffset,double yoffset);
    DllImport void Camera_FRMRate_Setting(int cameranumber,double framerate);
    DllImport void Camera_Burst_Setting(int cameranumber,double picnumber);
    DllImport void Machie_Run(int mashine_senario);
    DllImport void UpdatePixmap(double New_Min_Pix_To_Mm,double New_Max_Pix_To_Mm);

    QVector<bool> Camera_Connection_Flag;
    plcmodbusconnect* plcmodbusconnect_;
    plcmodbusRW* plcmodbusRW_;
    Machine* Machine_;
    MachineSetting_con* machinesetting_;
    MachineManager* MachineManager_;
    QStringList cameraname;
    Available_Cameras *Available_Cameras_;
    QVector<ZDS_camera_parameter*> ZDS_camera_parameter_List;
    QVector<Camera_Live*> Camera_Live_List;
    QVector<FLInspection*> FLInspection_List;
    QVector<FLCalibration*> FLCalibration_List;
    CLInspection *CLInspection_;
    double newmin,newmax;
    int savenumber;
    struct Stations {
        static const int FL1=0;
        static const int FL2=1;
        static const int CL=2;
    };
    struct JacktestMode {
        static const int Jog=0;
        static const int Cycle=1;
        static const int Trigger=2;
    };
    struct CameraGrabMode {
        static const int Live=0;
        static const int Trigger=1;
    };
    struct Direction {
        static const bool forward=true;
        static const bool backward=false;
    };
    struct ONOFF {
        static const bool ON=true;
        static const bool OFF=false;
    };
public slots:
    void Inpection_Result_Recived(HalconCpp::HImage* im,double minoval,double maxoval,bool AcceptFlag,int Station);
    void Calibration_Result_Recived(HalconCpp::HImage*im,double minoval ,double maxoval,int Station);
    void Connection_SettingPreview(HalconCpp::HImage*im);
    void CL_Inspection_Result_Recived(HalconCpp::HImage *im,double score,bool AcceptFlag);
signals:
    void ConnectionLayer_Inpection_Result(HalconCpp::HImage*im,double minoval,
                                          double maxoval,bool AcceptFlag,int station);
    void ConnectionLayer_Calibration_Result(HalconCpp::HImage*im,double maxoval ,double minoval,int station);
    void ConnectionLayer_Setting_Result(HalconCpp::HImage*im);
    void failed_connects_C(QString error);
    void connectionLayer_CL_Inpection_Result(HalconCpp::HImage *im,double score,bool AcceptFlag);
};

#endif // CONNECTIONS_H
