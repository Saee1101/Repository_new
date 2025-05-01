#ifndef CAMERA_PARAMETER_H
#define CAMERA_PARAMETER_H
#include <HalconCpp.h>
#include <QFile>
#include <QJsonParseError>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMap>
#include <QVector>
#include <QVariant>
#include <QObject>
#include "Plc_Classes/plcmodbusrw.h"
using namespace HalconCpp;
using namespace std;

class Camera_Parameter : public QObject
{
    Q_OBJECT
public:
    explicit Camera_Parameter(QObject *parent = nullptr);
    HFramegrabber  *grabber;
    QString camname;
    QString company_name;
    QStringList ParametersNameList;
    void Camera_Construction(QString CameraName);
    void Camera_Read_Configuration_From_Json(QString JsonAdress);
    void Camera_Set_Parameters_List(QStringList ParameterNameList,QVector<QVariant> ParametersValueList);
    HFramegrabber* Camera_Get_Grabber();
    void Camera_Update_Params(QVector<QVariant> ParameterList);
    void CameraGetParamList(QStringList ParameterNameList);
    void Camera_Get_Params();
    void SetPlcModbusRW(plcmodbusRW *plc);
    void Camera_Set_Grabber(HFramegrabber* g);
    int cameradelayaddres;
    void Camera_Trigger_Input_Delay_Address(int delayaddress);
    void Camera_Set_Delay(int delay);
    plcmodbusRW *device;
    QVector<QVariant> send_param;
    virtual void Camera_Set_Exposure(int exposure) const=0;
    virtual void Camera_Set_Grabbing_Mode(bool type) const =0;
    virtual void Camera_Set_ROI(int xoffset,int yoffset,int width,int height)const =0;
    virtual void Camera_Burst_Mode_Enable(bool,int)const = 0;
    virtual void Camera_Set_FrameRate(int framerate) const = 0;
    virtual void Camera_Set_Grabbing_Senario(int senario)const = 0;
    virtual void Camera_Set_Picture_Count(int picturecount)const=0;
    struct CommandType{
        static const bool software = true;
        static const bool hardware= false;
    };
    struct senario{
        static const int softwarefreerun = 0;
        static const int triggerfreerun= 1;
        static const int triggerburstrun= 2;
        static const int softwareburstrun = 3;
    };

public slots:

signals:
    void cameraImagesend_Capture(HalconCpp::HImage*);


};
// namespace company {
// namespace ZSD{
// int exposuretime=0;
// int xoffset=1;
// int yoffset=2;
// int wigth = 3;
// int height = 3;
// int
// }
// }

#endif // CAMERA_PARAMETER_H
