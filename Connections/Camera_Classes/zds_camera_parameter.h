#ifndef ZDS_CAMERA_PARAMETER_H
#define ZDS_CAMERA_PARAMETER_H

#include <QObject>
#include "camera_parameter.h"

class ZDS_camera_parameter : public Camera_Parameter
{
    Q_OBJECT
public:
    explicit ZDS_camera_parameter(QObject *parent = nullptr);
    void Camera_Set_Exposure(int exposure)const override;
    void Camera_Set_Grabbing_Mode(bool type) const override;
    void  Camera_Set_ROI(int xoffset,int yoffset,int width,int height)const override;
    void Camera_Burst_Mode_Enable(bool,int)const override;
    void Camera_Set_FrameRate(int framerate) const override;
    void Camera_Set_Grabbing_Senario(int senario)const override;
    void Camera_Set_Picture_Count(int count) const override;
        // grabber->SetFramegrabberParam( "TriggerCount", pictureCount);

};

#endif // ZDS_CAMERA_PARAMETER_H
