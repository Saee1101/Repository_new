#include "halconqtwindow.h"

halconqtwindow::halconqtwindow(QWidget *parent,long Width ,long Height) : QWidget(parent)
{
    //openwindow();
}

void halconqtwindow::openwindow(int windowwidth,int windowheight)
{
    using namespace HalconCpp;
   // HalconCpp::OpenWindow(0,0,640,480,(Hlong)winId(),"visible","",&WindID);
    Wind.OpenWindow(0,0,windowwidth,windowheight,(Hlong)winId(),"visible","");
}
