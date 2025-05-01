#include "camera_capture.h"

Camera_Capture::Camera_Capture(QObject *parent) : QThread(parent)
{

}

void Camera_Capture::Set_Grabber_name_Capture(HFramegrabber *grabber)
{
    CaptureGrabber = grabber;
}

void Camera_Capture::run()
{
    HString type;
    type="byte";
    QElapsedTimer timer;

    captured_Count = 0;

    CaptureGrabber->SetFramegrabberParam( "TriggerCount", Picture_Count );

    timer.start();
    CaptureGrabber->GrabImageStart(-1);

        while (cond_Capture == 1) {
            imageread.GrabImageAsync(*CaptureGrabber,-1);

            emit cameraImagesend_Capture(&imageread);
            if(Save_or_Not)
                imageread.WriteImage("tiff",0,QString::number(captured_Count).toStdString().c_str());
            captured_Count ++;
            qDebug() << "captureeeeeeeeeeeeee :::" << captured_Count;
            if(captured_Count == Picture_Count){
                cond_Capture = 0;
            }
//            else{
//                continue;
//            }
        }

    //        imageread.WriteImage("tiff",0,QString::number(i).toStdString().c_str());

    //    for (int i=0 ; i<Picture_Count ;i++) {
    //        try
    //        {
    //         imageread.GrabImageAsync(*CaptureGrabber,-1);
    //         emit cameraImagesend_Capture(&imageread);
    //        }
    //        catch (HException except)
    //        {
    //            qDebug()<<"exception timeout";
    //            continue;
    //        }
    //}


    //    Close_Frame_Capture();
}

void Camera_Capture::Close_Frame_Capture()
{
    CaptureGrabber->Clear();
}
