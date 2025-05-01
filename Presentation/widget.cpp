#include "MainWindow.h"
#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <string>
#include <QtCore>
#include <QDebug>
#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;

HTuple hv_Devices , hv_Information;
HString information , information2;
HTuple ValueList , ValueList2;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
power_system_flag = true;


ui->setupUi(this);

rejectsystemflag_D4 = false;
rejectsystemflag_D5 = false;
rejectsystemflag_CL = false;




FL = 0;
CL = 0;
ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

///////////////////////////////////////////////////////////////////////////////



ui->FL_Camera_Combo->model()->setData(ui->FL_Camera_Combo->model()->index(0, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo->model()->setData(ui->FL_Camera_Combo->model()->index(0, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");

ui->FL_Camera_Combo_4->model()->setData(ui->FL_Camera_Combo_4->model()->index(0, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_4->model()->setData(ui->FL_Camera_Combo_4->model()->index(0, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_4->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");

ui->FL_Camera_Combo_4->model()->setData(ui->FL_Camera_Combo_4->model()->index(1, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_4->model()->setData(ui->FL_Camera_Combo_4->model()->index(1, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_4->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");


ui->FL_Camera_Combo_3->model()->setData(ui->FL_Camera_Combo_3->model()->index(0, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_3->model()->setData(ui->FL_Camera_Combo_3->model()->index(0, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_3->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");

ui->FL_Camera_Combo_3->model()->setData(ui->FL_Camera_Combo_3->model()->index(1, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_3->model()->setData(ui->FL_Camera_Combo_3->model()->index(1, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_3->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");


ui->FL_Camera_Combo_2->model()->setData(ui->FL_Camera_Combo_2->model()->index(0, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_2->model()->setData(ui->FL_Camera_Combo_2->model()->index(0, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_2->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");


ui->FL_Camera_Combo_2->model()->setData(ui->FL_Camera_Combo_2->model()->index(1, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo_2->model()->setData(ui->FL_Camera_Combo_2->model()->index(1, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo_2->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");

ui->FL_Camera_Combo->model()->setData(ui->FL_Camera_Combo->model()->index(1, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
ui->FL_Camera_Combo->model()->setData(ui->FL_Camera_Combo->model()->index(1, 0), QColor("black"), Qt::ForegroundRole);
ui->FL_Camera_Combo->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");
//////////////////////////////////////////////////////////////


keyboard = new QProcess(this);

// connect(this,SIGNAL(enable_buttons_signal()),this,SLOT(enable_buttons_slot()));
//connect(this,SIGNAL(disable_buttons_signal()),this,SLOT(disable_buttons_slot()));
//connect(CCamera2,SIGNAL(Calib_Result_send(HalconCpp::HImage*,double,double);()),this,SLOT(PLC_FL2_Calib_Command()));
//connect(CCamera1,SIGNAL(Calib_Result_send(HalconCpp::HImage*,double,double);()),this,SLOT(PLC_FL2_Calib_Command()));

// connect(this,SIGNAL(enable_start()),this,SLOT(enable_start_slot()));
// connect(this,SIGNAL(disable_start()),this,SLOT(disable_start_slot()));
// connect(this,SIGNAL(set_camera_name()),this,SLOT(InitCamera()));


/////////////////////////////////////////////////////////////////
ui->D5_NewSample->setValidator(new QDoubleValidator(this));
ui->D4_NewSample->setValidator(new QDoubleValidator(this));

ui->Ovality_NewSample_D5->setValidator(new QDoubleValidator(this));
ui->TelN_NewSample_D5->setValidator(new QDoubleValidator(this));
ui->TelP_NewSample_D5->setValidator(new QDoubleValidator(this));
ui->Ovality_NewSample_D4->setValidator(new QDoubleValidator(this));
ui->TelN_NewSample_D4->setValidator(new QDoubleValidator(this));
ui->TelP_NewSample_D4->setValidator(new QDoubleValidator(this));
ui->RejectTime_RS->setValidator(new QDoubleValidator(this));
ui->RejectDelay_RS->setValidator(new QDoubleValidator(this));
ui->D5_editSample->setValidator(new QDoubleValidator(this));
ui->ovality_editSample_D5->setValidator(new QDoubleValidator(this));
ui->TelP_editSample_D5->setValidator(new QDoubleValidator(this));
ui->TelN_editSample_D5->setValidator(new QDoubleValidator(this));
ui->D4_editSample->setValidator(new QDoubleValidator(this));
ui->ovality_editSample_D4->setValidator(new QDoubleValidator(this));
ui->TelP_editSample_D4->setValidator(new QDoubleValidator(this));
ui->TelN_editSample_D4->setValidator(new QDoubleValidator(this));

ui->lineEdit_19_max->setValidator(new QDoubleValidator(this));
ui->lineEdit_20_min->setValidator(new QDoubleValidator(this));
ui->lineEdit_D4_max->setValidator(new QDoubleValidator(this));
ui->lineEdit_D4_min->setValidator(new QDoubleValidator(this));
ui->lineEdit_D5_max->setValidator(new QDoubleValidator(this));
ui->lineEdit_D5_min->setValidator(new QDoubleValidator(this));
Mesure_CameraCalibration2 = new halconqtwindow(this);
Mesure_CameraCalibration1 = new halconqtwindow(this);



OpticSettingCameraCL = new halconqtwindow(this);
OpticSettingCamera2 = new halconqtwindow(this);
DelaySettingCameraCL = new halconqtwindow(this);
DelaySettingCamera2 = new halconqtwindow(this);
DelaySettingCameraCL_2 = new halconqtwindow(this);
DelaySettingCamera2_2 = new halconqtwindow(this);
RejectSettingCamera2= new halconqtwindow(this);

Mesure_CameraCalibration2->openwindow(396,322);
Mesure_CameraCalibration1->openwindow(396,322);


OpticSettingCameraCL->openwindow(541,441);
OpticSettingCamera2->openwindow(541,441);
DelaySettingCameraCL->openwindow(391,321);
DelaySettingCamera2->openwindow(391,321);
DelaySettingCameraCL_2->openwindow(391,321);
DelaySettingCamera2_2->openwindow(391,321);

RejectSettingCamera2->openwindow(391,321);
ui->CL_OpticSetting_Camera_layout->addWidget(OpticSettingCameraCL);
ui->Fl2_OpticSetting_Camera_layout->addWidget(OpticSettingCamera2);
ui->Fl2_DelaySetting_Camera_layout->addWidget(DelaySettingCamera2);
ui->CL_DelaySetting_Camera_layout->addWidget(DelaySettingCameraCL);
ui->Fl2_DelaySetting_Camera_layout2->addWidget(DelaySettingCamera2_2);
ui->CL_DelaySetting_Camera_layout2->addWidget(DelaySettingCameraCL_2);
ui->FL2_RejectSetting_Camera_Layout->addWidget(RejectSettingCamera2);

ui->mesure_layout2->addWidget(Mesure_CameraCalibration2);
ui->mesure_layout->addWidget(Mesure_CameraCalibration1);

}

////////////////////////////////////////////////////////////////////////

Widget::~Widget()
{
    delete ui;
}

void Widget::UpdateUIFromDB()
{
    Business_logic_layer->entities.loadData();
    ui->EXPOSURE_CL_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Exposure_fl3"));
    ui->EXPOSURE_FL2_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Exposure_fl2"));
    ui->EXPOSURE_FL1_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Exposure_fl1"));
    ui->liftDelay_FL2_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("lift_delay_fl"));
    ui->liftTime_FL2_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("lift_time_fl"));
    ui->liftTime_CL_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("lift_time_cl"));
    ui->liftDelay_CL_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("lift_delay_cl"));
    ui->CameraDelay_DS_FL1->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Delay_fl1"));
    ui->CameraDelay_DS_FL2->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Delay_fl2"));
    ui->CameraDelay_DS_CL->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("Delay_fl3"));
    ui->CameraInterval_DS_CL->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("FrameRate_fl3"));
    ui->PictureCount_lineEdit->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("picture_count_cl"));
    ui->RejectDelay_RS->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("reject_delay"));
    ui->RejectTime_RS->setText(Business_logic_layer->entities.dataMap_machine_setting_db.value("reject_time"));
}



/// ////////////////////////////////////////////////////////////////////




void Widget::on_Keyboard_DelaySetting_clicked()
{
    keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_DelaySetting04_clicked()
{
        keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_DelaySetting03_clicked()
{
        keyboard->start("FreeVK.exe");
}

// void Widget::on_Keyboard_DelaySetting02_clicked()
// {
//         keyboard->start("FreeVK.exe");
// }

// void Widget::on_Keyboard_Mesure_clicked()
// {
//   keyboard->start("FreeVK.exe");
// }

void Widget::on_Keyboard_RejectSetting_clicked()
{
      keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_NewSample_clicked()
{
    keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_NS08_clicked()
{
    keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_EditSample_clicked()
{
        keyboard->start("FreeVK.exe");
}

void Widget::on_Keyboard_NS07_3_clicked()
{
        keyboard->start("FreeVK.exe");
}



void Widget::on_OpticSetting_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack1);
    ui->stackedWidget->setCurrentWidget(ui->OpticSetting01);
}

void Widget::on_DelaySetting_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack1);
    ui->stackedWidget->setCurrentWidget(ui->DelaySetting01);
}

void Widget::on_RejectSetting_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack1);
    ui->stackedWidget->setCurrentWidget(ui->RejectSetting01);
}

void Widget::on_Mesure_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure01);
}

void Widget::on_NewSample_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->NewSample01);
}

void Widget::on_EditSample_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack2);
    ui->stackedWidget_2->setCurrentWidget(ui->EditSample01);
}

void Widget::on_SampleSelection_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack2);
    ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection01);
}

void Widget::on_Next_NS08_2_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

    ui->sampleName_editSample_comboBox->clear();

   ui->D5_editSample->setText("");
    ui->TelP_editSample_D5->setText("");
    ui->TelN_editSample_D5->setText("");
    ui->ovality_editSample_D5->setText("");

    ui->D4_editSample->setText("");
    ui->TelP_editSample_D4->setText("");
    ui->TelN_editSample_D4->setText("");
    ui->ovality_editSample_D4->setText("");
}


void Widget::RejectTriggerImageCamera2(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    RejectSettingCamera2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(RejectSettingCamera2->WinfoeID());
}

void Widget::DelayPreviewImageRecived1_2(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    DelaySettingCameraCL_2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(DelaySettingCameraCL_2->WinfoeID());
}

void Widget::DelayPreviewImageRecived2_2(HImage *im)
{
    Hlong Width,Height;
    qDebug()<<"fromfl2";
    im->GetImageSize(&Width,&Height);
    DelaySettingCamera2_2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(DelaySettingCamera2_2->WinfoeID());

}

void Widget::DelayPreviewImageRecived1(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    DelaySettingCameraCL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(DelaySettingCameraCL->WinfoeID());

}

void Widget::DelayPreviewImageRecived2(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    DelaySettingCamera2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(DelaySettingCamera2->WinfoeID());
}

void Widget::OpticPreviewImageRecived1(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    OpticSettingCameraCL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(OpticSettingCameraCL->WinfoeID());
}

void Widget::OpticPreviewImageRecived2(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    OpticSettingCamera2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(OpticSettingCamera2->WinfoeID());
}



void Widget::Mesure_Result2(HImage *im , double d5_min , double d5_max )
{    Hlong Width,Height;
     im->GetImageSize(&Width,&Height);
     Mesure_CameraCalibration2->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
     im->DispColor(Mesure_CameraCalibration2->WinfoeID());
             double pixtomm2_max,pixtomm2_min;
             pixtomm2_max=D5_max_User/d5_max;
             FlPixtoMM2_max =pixtomm2_max;
             ui->FL2_M_lineEdit_2->setText(QString::number(pixtomm2_max*d5_max));
             pixtomm2_min=D5_min_User/d5_min;
             FlPixtoMM2_min =pixtomm2_min;
             ui->FL2_M_lineEdit_2_min->setText(QString::number(pixtomm2_min*d5_min));
             Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
             ui->StartCalibration_FL2_2->setEnabled(true);
             disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Calibration_Result(HalconCpp::HImage*,double,double,int)),this,SLOT(Mesure_Result2(HalconCpp::HImage*,double,double)));



}


void Widget::Mesure_Result1(HImage *im , double d4_min , double d4_max )
{    Hlong Width,Height;
     im->GetImageSize(&Width,&Height);
     Mesure_CameraCalibration1->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
     im->DispColor(Mesure_CameraCalibration1->WinfoeID());
             double pixtomm_max,pixtomm_min;
             pixtomm_max=D4_max_User/d4_max;
             FlPixtoMM1_max =pixtomm_max;
             ui->lineEdit_19_max->setText(QString::number(pixtomm_max*d4_max));
             pixtomm_min=D4_min_User/d4_min;
             FlPixtoMM1_min =pixtomm_min;
             ui->lineEdit_20_min->setText(QString::number(pixtomm_min*d4_min));
             Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
             ui->StartCalibration_FL2_3->setEnabled(true);
             disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Calibration_Result(HalconCpp::HImage*,double,double,int)),this,SLOT(Mesure_Result1(HalconCpp::HImage*,double,double)));

}

void Widget::on_BacktoMonitoring_btn_clicked()
{
        this->close();

}


void Widget::on_shutdown_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->ShutdownPage);
}


void Widget::on_shutdown_second_btn_clicked()
{
        emit(stop_power_system());


          QProcess::startDetached("shutdown -s -f -t 00");
}



void Widget::on_back_to_machine_setting_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

}


void Widget::on_Next_OS01_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OpticSetting02);
}



void Widget::on_CL_OS_clicked()
{
    CL = 1;

    ui->CL_OS->resize(148,120);
    ui->FL2_OS->resize(135,109);
}

void Widget::on_FL2_OS_clicked()
{
    FL = 1;

    ui->CL_OS->resize(135,109);
    ui->FL2_OS->resize(148,120);
}

void Widget::on_Next_OS02_clicked()
{
    if (CL==1){
        if(power_system_flag==true){
        ui->stackedWidget->setCurrentWidget(ui->OpticSetting04);
        }
        else{
        ui->stackedWidget->setCurrentWidget(ui->OpticSetting05);
            }
        }

    else if (FL == 1){
        if(power_system_flag==true){
            ui->stackedWidget->setCurrentWidget(ui->OpticSetting03);
        }
        else{
        ui->stackedWidget->setCurrentWidget(ui->OpticSetting06);
            }
        }
    FL=0;
    CL=0;


    ui->CL_OS->resize(135,109);
    ui->FL2_OS->resize(135,109);
}


void Widget::on_Cancel_OS_FL_clicked()
{

    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_Stop_Static_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OpticSetting06);

    emit(stop_power_system());
}

void Widget::on_Stop_Static_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DelaySetting06);
    emit(stop_power_system());
}


void Widget::on_Cancel_OS_CL_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_Stop_Static_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OpticSetting05);

    emit(stop_power_system());
}


void Widget::on_Next_OS_CL_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->OpticSetting08);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(OpticPreviewImageRecived1(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::CLsetting);

}


void Widget::on_Next_OS_FL2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OpticSetting07);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(OpticPreviewImageRecived2(HalconCpp::HImage*)));
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);
}


void Widget::on_Done_OS_FL_clicked()
{

    disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(OpticPreviewImageRecived2(HalconCpp::HImage*)));
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
    ui->FL_Camera_Combo->setCurrentIndex(0);
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
}


void Widget::on_Done_OS_CL_clicked()
{

        ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
        ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
        disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(OpticPreviewImageRecived1(HalconCpp::HImage*)));
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
}


void Widget::on_Next_DS_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DelaySetting02);
}


void Widget::on_CL_DS_clicked()
{
    CL = 1;
    ui->CL_DS->resize(148,120);
    ui->FL2_DS->resize(135,109);
}


void Widget::on_FL2_DS_clicked()
{
    FL = 1;
    ui->FL2_DS->resize(148,120);
    ui->CL_DS->resize(135,109);
}

void Widget::on_Next_DS_2_clicked()
{
    if(FL==1) {
        if(power_system_flag==true){
            ui->stackedWidget->setCurrentWidget(ui->DelaySetting03);

            }
        else{
        ui->stackedWidget->setCurrentWidget(ui->DelaySetting06);
            }
        }

    else if(CL==1){
        if(power_system_flag){
            ui->stackedWidget->setCurrentWidget(ui->DelaySetting04);

        }else{
        ui->stackedWidget->setCurrentWidget(ui->DelaySetting05);}
    }
    FL=0;
    CL=0;

    ui->CL_DS->resize(135,109);
    ui->FL2_DS->resize(135,109);
}


void Widget::on_Cancel_DS_FL_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_Cancel_DS_CL_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_Stop_Static_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DelaySetting05);

    emit(stop_power_system());
}

void Widget::on_Next_DS_CL_clicked()
{

        ui->stackedWidget->setCurrentWidget(ui->DelaySetting08);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived1(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::CLsetting);

}

void Widget::on_Next_DS_FL_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->DelaySetting07);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived2(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);


}

void Widget::on_Next_DS_3_clicked()
{
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived2_2(HalconCpp::HImage*)));
    disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived2(HalconCpp::HImage*)));
    ui->stackedWidget->setCurrentWidget(ui->DelaySetting09);
    ui->FL_Camera_Combo_2->setCurrentIndex(0);
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);
    //setdatatoplc


}

void Widget::on_Test_DS_FL_clicked()
{

          Business_logic_layer->connectionlayer.JackTest(Connections::Stations::FL1,ui->liftDelay_FL2_lineEdit->text().toDouble()
                                                                                   ,ui->liftTime_FL2_lineEdit->text().toDouble(),Connections::JacktestMode::Cycle,true);
          Business_logic_layer->connectionlayer.JackTest(Connections::Stations::FL2,ui->liftDelay_FL2_lineEdit->text().toDouble()
                                                                                   ,ui->liftTime_FL2_lineEdit->text().toDouble(),Connections::JacktestMode::Cycle,true);

          int LiftDelay,LiftTime;

          if(ui->liftDelay_FL2_lineEdit->text().isEmpty()){
              LiftDelay = 0;
          }
          else{
              LiftDelay=ui->liftDelay_FL2_lineEdit->text().toInt();
          }

          if(ui->liftTime_FL2_lineEdit->text().isEmpty()){
              LiftTime = 0;
          }
          else{
              LiftTime=ui->liftTime_FL2_lineEdit->text().toInt();
          }



          // Business_logic_layer->entities.CRUD_machine_setting_db.update("lift_delay_fl",QString::number(LiftDelay));
          //  Business_logic_layer->entities.CRUD_machine_setting_db.update("lift_time_fl",QString::number(LiftTime));

          QVariantMap data;

          data["lift_delay_fl"] = QString::number(LiftDelay);
          data["lift_time_fl"] = QString::number(LiftTime);


          QString condition = "id = 1";

          // فراخوانی متد update
          if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
              qDebug() << "Failed to update machine settings!";
          } else {
              qDebug() << "Machine settings updated successfully!";
          }
              dialog=new Dialog_;
              dialog->setObjectName("dialog_Musere");
              dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
              dialog->setGeometry(90,370,1030,247);
              dialog->setStyleSheet("#dialog_Musere{	background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 22.png);}");
              dialog->show();


}


void Widget::on_Next_DS_CL_2_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->DelaySetting10);


     ui->CameraDelay_DS_CL->setEnabled(true);
     ui->CameraInterval_DS_CL->setEnabled(true);
     ui->PictureCount_lineEdit->setEnabled(true);
     disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived1(HalconCpp::HImage*)));
     Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
     connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived1_2(HalconCpp::HImage*)));
     Business_logic_layer->System_Set_Mode(Business_logic::Mode::CLsetting);


}

void Widget::on_Test_DS_CL_clicked()
{


        int LiftDelay,LiftTime;

              if(ui->liftTime_CL_lineEdit->text().isEmpty()){
                  LiftTime = 0;
              }
              else{
                  LiftTime=ui->liftTime_CL_lineEdit->text().toInt();
              }

              if(ui->liftDelay_CL_lineEdit->text().isEmpty()){
                  LiftDelay = 0;
              }
              else{
              LiftDelay=ui->liftDelay_CL_lineEdit->text().toInt();}

              // Business_logic_layer->entities.CRUD_machine_setting_db.Update("lift_delay_cl",QString::number(LiftDelay));
              // Business_logic_layer->entities.CRUD_machine_setting_db.Update("llift_time_cl",QString::number(LiftTime));

              QVariantMap data;

              data["lift_delay_fl"] = QString::number(LiftDelay);
              data["lift_time_fl"] = QString::number(LiftTime);


              QString condition = "id = 1";

              // فراخوانی متد update
              if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
                  qDebug() << "Failed to update machine settings!";
              } else {
                  qDebug() << "Machine settings updated successfully!";
              }

                  dialog=new Dialog_;
                  dialog->setObjectName("dialog_DS");
                  dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
                  dialog->setGeometry(90,370,1030,247);
                  dialog->setStyleSheet("#dialog_DS {background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 22.png);}");
                  dialog->show();



              Business_logic_layer->connectionlayer.JackTest(Connections::Stations::CL,LiftDelay,LiftTime,Connections::JacktestMode::Cycle,true);


}


void Widget::on_Done_DS_FL2_clicked()
{
    disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived2_2(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
    ui->FL_Camera_Combo_3->setCurrentIndex(0);


}



void Widget::on_Test_DS_FL2_clicked()
{



    int CameraDelay_fl1 , CameraDelay_fl2;

          if(ui->CameraDelay_DS_FL2->text().isEmpty()){
              CameraDelay_fl2 = 0;
          }
          else{
          CameraDelay_fl2=ui->CameraDelay_DS_FL2->text().toInt();}

          if(ui->CameraDelay_DS_FL1->text().isEmpty()){
              CameraDelay_fl1 = 0;
          }
          else{
          CameraDelay_fl1=ui->CameraDelay_DS_FL1->text().toInt();
          }
          Business_logic_layer->connectionlayer.Camera_Delay_Setting(Connections::Stations::FL1,CameraDelay_fl1);
          Business_logic_layer->connectionlayer.Camera_Delay_Setting(Connections::Stations::FL2,CameraDelay_fl2);




          // q.prepare("UPDATE machine_setting SET camera_delay_fl2=? , camera_delay_fl1=? WHERE id = 1");
          // q.addBindValue(CameraDelay_fl2);
          // q.addBindValue(CameraDelay_fl1);
          // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Delay_fl1",QString::number(CameraDelay_fl1));
          // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Delay_fl2",QString::number(CameraDelay_fl2));

          QVariantMap data;
          // افزودن داده‌های جدید برای ستون‌ها
          data["Delay_fl1"] = QString::number(CameraDelay_fl1);
          data["Delay_fl2"] = QString::number(CameraDelay_fl2);

          // شرط به‌روزرسانی: فرض کنیم می‌خواهید رکوردی با id = 1 به‌روزرسانی کنید
          QString condition = "id = 1";

          // فراخوانی متد update
          if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
              qDebug() << "Failed to update machine settings!";
          } else {
              qDebug() << "Machine settings updated successfully!";
          }


              dialog=new Dialog_;
              dialog->setObjectName("dialog_DS");
              dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
              dialog->setGeometry(90,370,1030,247);
              dialog->setStyleSheet("#dialog_DS {background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 22.png);}");
              dialog->show();





}



void Widget::on_Done_DS_CL_clicked()
{
    disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(DelayPreviewImageRecived1_2(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    qDebug()<<"stop";
//    emit(enable_start());

   //  dialog=new Dialog_;
   //  dialog->setObjectName("dialog_Musere");
   //  dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
   //  dialog->setGeometry(90,370,1030,247);
   //  dialog->setStyleSheet("#dialog_Musere{	background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 22.png);}");
   //  dialog->show();

   // connect(dialog->pushbutton,SIGNAL(clicked()),this,SLOT(DelaySetting_close()));
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);



}

void Widget::DelaySetting_close()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
      ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_Start_DS_CL_2_clicked()
{


   int CameraDelay,CameraInterval,PictureCount;

   if(ui->CameraDelay_DS_CL->text().isEmpty()){
       CameraDelay = 0;
   }
   else{
       CameraDelay=ui->CameraDelay_DS_CL->text().toInt();}

   if(ui->CameraInterval_DS_CL->text().isEmpty()){
       CameraInterval = 0;
   }
   else{
       CameraInterval=ui->CameraInterval_DS_CL->text().toInt();}

   if(ui->PictureCount_lineEdit->text().isEmpty()){
       PictureCount = 0;
   }
   else{
       PictureCount=ui->PictureCount_lineEdit->text().toInt();}











   ui->CameraDelay_DS_CL->setEnabled(false);
   ui->CameraInterval_DS_CL->setEnabled(false);
   ui->PictureCount_lineEdit->setEnabled(false);

   // cl_camera_preview_start();

}




void Widget::on_Start_DS_CL_clicked()
{

        // emit(disable_start());


        int CameraDelay , CameraInterval , cameraPictureCount;
              if(ui->CameraDelay_DS_CL->text().isEmpty()){
                  CameraDelay = 0;
              }

              else{
              CameraDelay=ui->CameraDelay_DS_CL->text().toInt();}

              if(ui->CameraInterval_DS_CL->text().isEmpty()){

                  CameraInterval = 0;
              }
              else{

                      CameraInterval = ui->CameraInterval_DS_CL->text().toInt();
                  }

              if(ui->PictureCount_lineEdit->text().isEmpty()){

                  cameraPictureCount = 0;
              }
              else{

                  cameraPictureCount = ui->PictureCount_lineEdit->text().toInt();
              }
              Business_logic_layer->connectionlayer.Camera_Delay_Setting(Connections::Stations::CL,CameraDelay);
              Business_logic_layer->connectionlayer.Camera_Burst_Setting(Connections::Stations::CL,cameraPictureCount);
              Business_logic_layer->connectionlayer.Camera_FRMRate_Setting(Connections::Stations::CL,CameraInterval);
              Business_logic_layer->System_Set_Mode(Business_logic::Mode::CLsetting);

              // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Delay_fl3",QString::number(CameraDelay));
              // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Exposure_fl3",QString::number(CameraInterval));
              // Business_logic_layer->entities.CRUD_machine_setting_db.Update("picture_count_cl",QString::number(cameraPictureCount));
              QVariantMap data;

              data["Delay_fl3"] = QString::number(CameraDelay);
              data["Exposure_fl3"] = QString::number(CameraInterval);
              data["picture_count_cl"] = QString::number(cameraPictureCount);

              QString condition = "id = 1";

              // فراخوانی متد update
              if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
                  qDebug() << "Failed to update machine settings!";
              } else {
                  qDebug() << "Machine settings updated successfully!";
              }

              dialog=new Dialog_;
              dialog->setObjectName("dialog_DS_CL");
              dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
              dialog->setGeometry(90,370,1030,247);
              dialog->setStyleSheet("#dialog_DS_CL {background-color: rgba(0, 0, 0,0); border-image: url(:/resource/Image/Asset 22.png);}");
              dialog->show();

}

void Widget::on_Stop_DS_CL_clicked()
{
//     Preview_Camera_Stop(PCameraCL,true);
    // emit(enable_start());

    emit(enable_buttons_signal());
Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
     ui->CameraDelay_DS_CL->setEnabled(true);
     ui->CameraInterval_DS_CL->setEnabled(true);
     ui->PictureCount_lineEdit->setEnabled(true);

}


void Widget::on_Next_RS01_clicked()
{
    if(power_system_flag==true){
        ui->stackedWidget->setCurrentWidget(ui->RejectSetting02);

    }else{
    ui->stackedWidget->setCurrentWidget(ui->RejectSetting03);}
}


// void Widget::on_Cancel_RS02_clicked()
// {
//     ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
//     ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
// }

void Widget::on_Stop_Static_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->RejectSetting03);

    emit(stop_power_system());
}


void Widget::on_Cancel_RS_clicked()

{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}


void Widget::on_Next_RS02_2_clicked()
{



    ui->stackedWidget->setCurrentWidget(ui->RejectSetting04);
        connect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(RejectTriggerImageCamera2(HalconCpp::HImage*)));
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);

}


void Widget::on_Done_RS_clicked()
{
    disconnect(Business_logic_layer,SIGNAL(BusinessLogic_Setting_Camera_Result(HalconCpp::HImage*)),this,SLOT(RejectTriggerImageCamera2(HalconCpp::HImage*)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
    ui->FL_Camera_Combo_4->setCurrentIndex(0);


}


void Widget::on_Test_RS_clicked()
{

    int RejectDelay,RejectTime;

          if(ui->RejectDelay_RS->text().isEmpty()){
              RejectDelay = 0;
          }
          else{
          RejectDelay=ui->RejectDelay_RS->text().toInt();
          }

          if(ui->RejectTime_RS->text().isEmpty()){
              RejectTime = 0;
          }
          else{
          RejectTime=ui->RejectTime_RS->text().toInt();
          }
          Business_logic_layer->connectionlayer.JackTest(4,RejectDelay,RejectTime,Connections::JacktestMode::Trigger,true);


          // Business_logic_layer->entities.CRUD_machine_setting_db.Update("reject_delay",QString::number(RejectDelay));
          // Business_logic_layer->entities.CRUD_machine_setting_db.Update("reject_time",QString::number(RejectTime));
          QVariantMap data;

          data["reject_delay"] = QString::number(RejectDelay);
          data["reject_time"] = QString::number(RejectTime);


          QString condition = "id = 1";

          // فراخوانی متد update
          if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
              qDebug() << "Failed to update machine settings!";
          } else {
              qDebug() << "Machine settings updated successfully!";
          }




              dialog=new Dialog_;
              dialog->setObjectName("dialog_RS");
              dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
              dialog->setGeometry(90,370,1030,247);
              dialog->setStyleSheet("#dialog_RS{	background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 22.png);}");
              dialog->show();


}




void Widget::on_Next_M01_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure02);
}



void Widget::on_Back_M_FL2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure04);
}

void Widget::on_Done_M_FL2_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);


    double Fl2_Pix_to_MM = ui->FL2_M_lineEdit_2->text().toDouble();


    // q.prepare("UPDATE machine_setting SET pixel_to_mm_fl2 where Id=1");
    // q.addBindValue(Fl2_Pix_to_MM);
    // q.exec();



}



void Widget::on_Next_NS01_clicked()
{
     ui->stackedWidget_3->setCurrentWidget(ui->NewSample02);
}


void Widget::on_FL2_NS01_clicked()
{
    FL = 2;
    ui->FL2_NS01->resize(148,120);
}

void Widget::on_Next_NS02_clicked()
{
    if (FL == 2){
        if(power_system_flag){
        ui->stackedWidget_3->setCurrentWidget(ui->NewSample03);}
        else{
            ui->stackedWidget_3->setCurrentWidget(ui->NewSample04);}
        }

    FL=0;

    ui->FL2_NS01->resize(135,109);

}


void Widget::on_Stop_NS01_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->NewSample04);

    emit(stop_power_system());
}

void Widget::on_Cancel_NS01_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}


void Widget::on_Next_NS05_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->NewSample05);
}


void Widget::on_set_newSample_clicked()
{
    // دریافت داده‌ها از رابط کاربری
    QString Name = ui->samplename_NewSample->text();
    QString D5 = ui->D5_NewSample->text();
    QString diamiter_max_fl2 = ui->TelP_NewSample_D5->text();
    QString diamiter_min_fl2 = ui->TelN_NewSample_D5->text();
    QString D5_ovality = ui->Ovality_NewSample_D5->text();

    QString D4 = ui->D4_NewSample->text();
    QString diamiter_max_fl1 = ui->TelP_NewSample_D4->text();
    QString diamiter_min_fl1 = ui->TelN_NewSample_D4->text();
    QString D4_ovality = ui->Ovality_NewSample_D4->text();

    // ساخت یک QVariantMap برای ذخیره تمام داده‌ها
    QVariantMap data;
    data["name"] = Name;
    data["diamiter_min_fl2"] = diamiter_min_fl2;
    data["diamiter_max_fl2"] = diamiter_max_fl2;
    data["d5_ovality"] = D5_ovality;
    data["d5"] = D5;
    data["diamiter_min_fl1"] = diamiter_min_fl1;
    data["diamiter_max_fl1"] = diamiter_max_fl1;
    data["d4_ovality"] = D4_ovality;
    data["d4"] = D4;

    // به‌روزرسانی داده‌ها در پایگاه داده
    QString condition = "id = 4"; // فرض کنید شرط بر اساس یک ستون کلیدی است (مانند id)
    if (!Business_logic_layer->entities.CRUD_sample_db_List.at(4)->update(condition, data)) {
        qDebug() << "Failed to update sample data!";
    } else {
        qDebug() << "Sample data updated successfully!";
    }

    // نمایش دیالوگ
    dialog = new Dialog_;
    dialog->setObjectName("dialog_Newsample");
    dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    dialog->setGeometry(90, 370, 1030, 247);
    dialog->setStyleSheet("#dialog_Newsample{ background-color: rgba(0, 0, 0, 0); border-image: url(:/Image/Asset 22.png); }");
    dialog->show();

    // پاک کردن داده‌های رابط کاربری
    ui->samplename_NewSample->setText("");
    ui->D5_NewSample->setText("");
    ui->TelP_NewSample_D5->setText("");
    ui->TelN_NewSample_D5->setText("");
    ui->Ovality_NewSample_D5->setText("");
    ui->D4_NewSample->setText("");
    ui->TelP_NewSample_D4->setText("");
    ui->TelN_NewSample_D4->setText("");
    ui->Ovality_NewSample_D4->setText("");
}


void Widget::on_Done_NS_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
    ui->samplename_NewSample->setText("");
    ui->D5_NewSample->setText("");
    ui->TelP_NewSample_D5->setText("");
    ui->TelN_NewSample_D5->setText("");
    ui->Ovality_NewSample_D5->setText("");
    ui->D4_NewSample->setText("");
    ui->TelP_NewSample_D4->setText("");
    ui->TelN_NewSample_D4->setText("");
    ui->Ovality_NewSample_D4->setText("");
}



void Widget::on_Next_ES01_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->EditSample02);
}


void Widget::on_FL2_ES01_clicked()
{
    FL = 2;
    ui->FL2_ES01->resize(148,120);
}


void Widget::on_Next_ES02_clicked()
{
    if (FL == 2){
        if(power_system_flag)
        {
        ui->stackedWidget_2->setCurrentWidget(ui->EditSample03);
        }
        else{
        ui->stackedWidget_2->setCurrentWidget(ui->EditSample04);}
    }
    FL=0;
    ui->FL2_ES01->resize(135,109);
}


void Widget::on_Stop_ES01_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->EditSample04);

    emit(stop_power_system());

}

void Widget::on_Cancel_ES01_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}


void Widget::on_Next_ES03_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->EditSample05);
}


void Widget::on_set_EditSample_clicked()
{

    QString currentName = ui->sampleName_editSample_comboBox->currentText();


    QString Name,D5,Telp_D5,Teln_D5,D5_ovality,D4,D4_ovality,Teln_D4,Telp_D4;

          D5=ui->D5_editSample->text();
          Telp_D5=ui->TelP_editSample_D5->text();
          Teln_D5=ui->TelN_editSample_D5->text();
          D5_ovality=ui->ovality_editSample_D5->text();

          D4=ui->D4_editSample->text();
          Telp_D4=ui->TelP_editSample_D4->text();
          Teln_D4=ui->TelN_editSample_D4->text();
          D4_ovality=ui->ovality_editSample_D4->text();






           //      dialog=new Dialog_;
           //      dialog->setObjectName("dialog_EditSample");
           //      dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
           //      dialog->setGeometry(90,370,1030,247);
           //      dialog->setStyleSheet("#dialog_EditSample{	background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 21.png);}");
           //      dialog->show();




}

void Widget::on_sampleName_editSample_comboBox_textActivated(const QString &arg1)
{

    QString currentName = ui->sampleName_editSample_comboBox->currentText();
}


void Widget::on_Next_SS01_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection02);
}

void Widget::on_FL2_SS01_clicked()
{
    FL = 2;
    ui->FL2_SS01->resize(148,120);
}

void Widget::on_Next_SS02_clicked()
{
    if (FL == 2)
    {   if(power_system_flag){
            ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection03);
        }
        else{
            ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection04);

        }}

    FL=0;
    ui->FL2_SS01->resize(135,109);

}


void Widget::on_Stop_SS01_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection04);

    emit(stop_power_system());

}

void Widget::on_Cancel_SS03_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}


void Widget::on_Next_SS05_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection05);

    for(int i=0;i<Business_logic_layer->entities.CRUD_sample_db_List.length();i++)
    {
        QList<Sample> samples = Business_logic_layer->entities.CRUD_sample_db_List.at(i)->readAll();
        for (const Sample& sample : samples) {
            ui->sampleSelection_comboBox->addItem(sample.getName());
        }

        // ui->sampleSelection_comboBox->model()->setData(ui->sampleSelection_comboBox->model()->index(i, 0), QColor(QColor(252,177,25)), Qt::BackgroundRole);
        // ui->sampleSelection_comboBox->model()->setData(ui->sampleSelection_comboBox->model()->index(i, 0), QColor("black"), Qt::ro);
        ui->sampleSelection_comboBox->view()->window()->setStyleSheet("border : 1px solid yellow; border-radius: 5px;");


    }

}


void Widget::on_sampleSelection_comboBox_textActivated(const QString &arg1)
{

    // QString currentName = ui->sampleSelection_comboBox->currentText();
   int currentNum= ui->sampleSelection_comboBox->currentIndex();
    qDebug()<<"currentsample"<<currentNum;
    // Business_logic_layer->entities.CRUD_sample_db_List.at(currentNum)->GetAll();
    QVariantMap data;
    data["sample_id"] = currentNum;
     QString condition = "id = 1";
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data);


}

void Widget::on_Next__SS07_clicked()
{
      ui->stackedWidget_2->setCurrentWidget(ui->SampleSelection06);
    Business_logic_layer->entities.loadData();

       bool  cl_status , fl1_status , fl2_status;
      double cl_stage ;
       // QString currentName = ui->sampleSelection_comboBox->currentText();

      // ui->sampleName_sampleSelection->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("name"));
      ui->sampleName_sampleSelection->setText(Business_logic_layer->entities.dataMap_sample_db.value("name"));
      // ui->D5_sampleSelection->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("d5"));
      ui->D5_sampleSelection->setText(Business_logic_layer->entities.dataMap_sample_db.value("d5"));
      // ui->TelP_SampleSelection_d5->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("diamiter_max_fl2"));
      ui->TelP_SampleSelection_d5->setText(Business_logic_layer->entities.dataMap_sample_db.value("diamiter_max_fl2"));
      // ui->TelN_SampleSelection_d5->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("diamiter_min_fl2"));
       ui->TelN_SampleSelection_d5->setText(Business_logic_layer->entities.dataMap_sample_db.value("diamiter_min_fl2"));
      // ui->Ovality_SampleSelection_d5->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("d5_ovality"));
        ui->Ovality_SampleSelection_d5->setText(Business_logic_layer->entities.dataMap_sample_db.value("d5_ovality"));
      // ui->D4_sampleSelection->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("d4"));
         ui->D4_sampleSelection->setText(Business_logic_layer->entities.dataMap_sample_db.value("d4"));
      // ui->TelP_SampleSelection_d4->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("diamiter_max_fl1"));
            ui->TelP_SampleSelection_d4->setText(Business_logic_layer->entities.dataMap_sample_db.value("diamiter_max_fl1"));
      // ui->TelN_SampleSelection_d4->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("diamiter_min_fl1"));
          ui->TelN_SampleSelection_d4->setText(Business_logic_layer->entities.dataMap_sample_db.value("diamiter_min_fl1"));
      // ui->Ovality_SampleSelection_d4->setText(Business_logic_layer->entities.CRUD_sample_db->GetValue("d4_ovality"));
           ui->Ovality_SampleSelection_d4->setText(Business_logic_layer->entities.dataMap_sample_db.value("d4_ovality"));

      cl_stage =Business_logic_layer->entities.CRUD_machine_setting_db.GetValue("cl_stage").toDouble() ;
      cl_status = Business_logic_layer->entities.CRUD_machine_setting_db.GetValue("cl_reject_status").toInt();
      fl1_status =  Business_logic_layer->entities.CRUD_machine_setting_db.GetValue("fl1_reject_status").toInt();
      fl2_status = Business_logic_layer->entities.CRUD_machine_setting_db.GetValue("fl2_reject_status").toInt();


        if(!fl1_status){
            rejectsystemflag_D4 = false;
            ui->btn_reject_D4->setStyleSheet("border-image: url(:/Image/R2.png);");
        }else if(fl1_status){
            rejectsystemflag_D4 = true ;
            ui->btn_reject_D4->setStyleSheet("border-image: url(:/Image/R1.png);");
        }

        if(!fl2_status){
            rejectsystemflag_D5 = false;
            ui->btn_reject_D5->setStyleSheet("border-image: url(:/Image/R2.png);");

        }else if(fl2_status){
            rejectsystemflag_D5 = true ;
            ui->btn_reject_D5->setStyleSheet("border-image: url(:/Image/R1.png);");
        }


        if(!cl_status){
            rejectsystemflag_CL = false;
            ui->btn_reject_CL->setStyleSheet("border-image: url(:/Image/R2.png);");

        }else if(cl_status){
            rejectsystemflag_CL = true ;
            ui->btn_reject_CL->setStyleSheet("border-image: url(:/Image/R1.png);");
        }
   qDebug()<<"cl stage ::::::"<<cl_stage;
   ui->doubleSpinBox_CL->setValue(cl_stage);

//       if(cl_stage==1){
//           ui->cl_stage_combo->setCurrentIndex(0);
//       }
//       else if(cl_stage==2){
//           ui->cl_stage_combo->setCurrentIndex(1);
//       }
//       else if(cl_stage==3){
//           ui->cl_stage_combo->setCurrentIndex(2);
//       }

   ui->doubleSpinBox_D4->setValue(Business_logic_layer->entities.CRUD_sample_db->GetValue("d4").toDouble());
   ui->doubleSpinBox_D5->setValue(Business_logic_layer->entities.CRUD_sample_db->GetValue("d5").toDouble());
       ui->sampleSelection_comboBox->clear();


}


void Widget::on_Back_SS01_clicked()
{
    on_Next_SS05_clicked();

}

void Widget::on_Done_SS01_clicked()
{
    int d4_status , d5_status , cl_status;
    double d4_sensitivity , d5_sensitivity;


    d4_sensitivity = ui->doubleSpinBox_D4->value();
    d5_sensitivity = ui->doubleSpinBox_D5->value();


    if(rejectsystemflag_D4==true){
        d4_status = 1;
    }else{
        d4_status = 0;
    }

    qDebug()<<"d4_status"<<d4_status;

    if(rejectsystemflag_D5==true){
        d5_status = 1;
    }else{
        d5_status = 0;
    }

    qDebug()<<"d5_status"<<d5_status;


    if(rejectsystemflag_CL==true){
        cl_status = 1;
    }else{
        cl_status = 0;
    }

    qDebug()<<"cl_status"<<cl_status;

    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

    ui->sampleName_sampleSelection->clear();
    ui->D5_sampleSelection->clear();
    ui->TelP_SampleSelection_d5->clear();
    ui->TelN_SampleSelection_d5->clear();
    ui->Ovality_SampleSelection_d5->clear();

    ui->D4_sampleSelection->clear();
    ui->TelP_SampleSelection_d4->clear();
    ui->TelN_SampleSelection_d4->clear();
    ui->Ovality_SampleSelection_d4->clear();


    qDebug()<<"set rejection signal has been sent";
    QVariantMap data;

    data["cl_stage"] = ui->doubleSpinBox_CL->text();
    data["cl_reject_status"] = QString::number(cl_status);
    data["fl1_reject_status"] = QString::number(d4_status);
    data["fl2_reject_status"] = QString::number(d5_status);


    QString condition = "id = 1";
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
    emit(set_MainWindow());
    emit(set_sensitivity());
    emit(set_rejection());
}

void Widget::on_Changepassword_btn_clicked()
{
      // Business_logic_layer->entities.CRUD_user_db.Update("admin",ui->lineEdit->text());
    changepassword =new Dialog_ChangePassWord(this);
changepassword->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
changepassword->setGeometry(390,170,480,510);
changepassword->show();
}



void Widget::enable_buttons_slot()
{
    ui->Done_OS_CL->setEnabled(true);
    ui->Done_OS_FL->setEnabled(true);
    ui->Done_M_FL2->setEnabled(true);
    ui->Back_M_FL2->setEnabled(true);
    ui->Done_RS->setEnabled(true);
    ui->Next_DS_3->setEnabled(true);
    ui->Next_DS_CL_2->setEnabled(true);
    ui->Done_DS_FL2->setEnabled(true);
    ui->Done_DS_CL->setEnabled(true);


}

void Widget::disable_buttons_slot()
{
    ui->Done_OS_CL->setEnabled(false);
    ui->Done_OS_FL->setEnabled(false);
    ui->Done_M_FL2->setEnabled(false);
    ui->Back_M_FL2->setEnabled(false);
    ui->Done_RS->setEnabled(false);
    ui->Next_DS_3->setEnabled(false);
    ui->Next_DS_CL_2->setEnabled(false);
    ui->Done_DS_FL2->setEnabled(false);
    ui->Done_DS_CL->setEnabled(false);


}

void Widget::disable_start_slot()
{
    ui->Start_DS_CL->setEnabled(false);
}

void Widget::enable_start_slot()
{
    ui->Start_DS_CL->setEnabled(true);
}


void Widget::on_back_from_devpage_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_set_dongle_clicked()
{
    // QSqlDatabase db;
    // db=QSqlDatabase :: addDatabase("QSQLITE");
    // db.setDatabaseName("ParsAmpoule_P3.db");
    // db.open();
    // QSqlQuery q;

    // QString StrUser = ui->struser_a->text();
    // QString StrSafekey = ui->strsafeykey->text();
    // QString StrSafekey2 = ui->strsafekey2->text();
    // QString StrAES = ui->straes->text();

    // q.prepare(QString("UPDATE dynamic_dongle SET strUser_A=? , strSafeKey_1 = ? , strSafeKey_2 = ? , strAES_A = ?"));
    // q.addBindValue(StrUser);
    // q.addBindValue(StrSafekey);
    // q.addBindValue(StrSafekey2);
    // q.addBindValue(StrAES);
    // q.exec();
    // q.first();

    // if(q.exec()){
    //     QMessageBox msg;
    //     msg.setText("Successful");
    //     msg.setWindowTitle("Information");
    //     msg.exec();


    // }

    ui->straes->clear();
    ui->struser_a->clear();
    ui->strsafekey2->clear();
    ui->strsafeykey->clear();


}

void Widget::on_set_plc_clicked()
{
    // QSqlDatabase db;
    // db=QSqlDatabase :: addDatabase("QSQLITE");
    // db.setDatabaseName("ParsAmpoule_P3.db");
    // db.open();
    // QSqlQuery q;

    // QString plc_name = ui->plc_name->text();


    // q.prepare(QString("UPDATE dynamic_plc SET name = ?"));
    // q.addBindValue(plc_name);

    // q.exec();
    // q.first();

    // emit(set_plc_name());

    // if(q.exec()){
    //     QMessageBox msg;
    //     msg.setText("Successful");
    //     msg.setWindowTitle("Information");
    //     msg.exec();


    // }

    // ui->plc_name->clear();

}


void Widget::on_fand_connected_cameras_clicked()
{
   // InfoFramegrabber("GigEVision2", "device", &hv_Information, &hv_Devices);
    //HInfo.InfoFramegrabber("GigEVision2", "device", ValueList);
information = HInfo::InfoFramegrabber("GigEVision2", "device", &ValueList);
    int i=0;
    QString my_operator = ":";
    while(i < (ValueList.Length())){

        QString current_device = QString(ValueList[i]);
        int from_ = current_device.indexOf(my_operator, 0);
        int to_ = current_device.indexOf(" ", 11);

        int length = to_-from_;

        QString name = current_device.mid(from_+1 , length-1);
        qDebug()<<"vvvvvvvvvvv"<<name;
        qDebug()<<"iiiiiiiiiiiii"<<length;


        qDebug()<<"index of of of <<"<<current_device.indexOf(my_operator, 57);
        qDebug()<<"index of of of <<"<<current_device.indexOf(" ", 68);

        ui->cameras_combo->addItem(name);
        i++;
    }

    qDebug()<<"camcam++"<<QString(ValueList[0])<<"//";

}

void Widget::on_cameras_combo_textActivated(const QString &arg1)
{

}

void Widget::on_set_camera_fl_clicked()
{

    QString cam_name_fl2 = ui->cameras_combo->currentText();

        // QSqlQuery q;
        // q.prepare("UPDATE dynamic_camera SET fl2_camera_name = ? ");
        // q.addBindValue(cam_name_fl2);
        // q.exec();
        // q.first();

        // if(q.exec()){
        //     QMessageBox msg;
        //     msg.setText("Successful");
        //     msg.setWindowTitle("Information");
        //     msg.exec();


        // }

        ui->cameras_combo->clear();

}

void Widget::on_cameras_combo_activated(int index)
{

}

void Widget::on_find_connected_cameras_cl_3_clicked()
{
    // InfoFramegrabber("GigEVision2", "device", &hv_Information, &hv_Devices);
     //HInfo.InfoFramegrabber("GigEVision2", "device", ValueList);
 information = HInfo::InfoFramegrabber("GigEVision2", "device", &ValueList);
     int i=0;
     QString my_operator = ":";
     while(i < (ValueList.Length())){

         QString current_device = QString(ValueList[i]);
         int from_ = current_device.indexOf(my_operator, 0);
         int to_ = current_device.indexOf(" ", 11);

         int length = to_-from_;

         QString name = current_device.mid(from_+1 , length-1);
         qDebug()<<"vvvvvvvvvvv"<<name;
         qDebug()<<"iiiiiiiiiiiii"<<length;


         qDebug()<<"index of of of <<"<<current_device.indexOf(my_operator, 57);
         qDebug()<<"index of of of <<"<<current_device.indexOf(" ", 68);

         ui->cameras_combo_cl->addItem(name);
         i++;
     }

     qDebug()<<"camcam++"<<QString(ValueList[0])<<"//";




}

void Widget::on_set_camera_cl_clicked()
{


    QString cam_name_cl = ui->cameras_combo_cl->currentText();

        // QSqlQuery q;
        // q.prepare("UPDATE dynamic_camera SET cl_camera_name = ? ");
        // q.addBindValue(cam_name_cl);
        // q.exec();
        // q.first();

        // if(q.exec()){
        //     QMessageBox msg;
        //     msg.setText("Successful");
        //     msg.setWindowTitle("Information");
        //     msg.exec();


        // }

        // ui->cameras_combo_cl->clear();

        // camera_slot();
}

void Widget::show_Devpage()
{
    ui->stackedWidget_3->setCurrentWidget(ui->DevelopersPage);

}

void Widget::on_pushButton_2_clicked()
{
    this->close();
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
}

void Widget::on_FL_Camera_Combo_currentIndexChanged(int index)
{
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    if(index==0){
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);
    }
    else if(index==1){
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL2setting);
    }

}



void Widget::on_FL_Camera_Combo_2_currentIndexChanged(int index)
{
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    if(index==0){
Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);
    }
    else if(index==1){
Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL2setting);
    }
}

void Widget::on_FL_Camera_Combo_3_currentIndexChanged(int index)
{
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);

    if(index==0){
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);

    }
    else if(index==1){
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL2setting);

    }
}


void Widget::on_FL_Camera_Combo_4_currentIndexChanged(int index)
{
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);

    if(index==0){

        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1setting);


    }
    else if(index==1){

        Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL2setting);


    }
}


void Widget::on_fand_connected_cameras_2_clicked()
{
    // InfoFramegrabber("GigEVision2", "device", &hv_Information, &hv_Devices);
     //HInfo.InfoFramegrabber("GigEVision2", "device", ValueList);
 information = HInfo::InfoFramegrabber("GigEVision2", "device", &ValueList);
     int i=0;
     QString my_operator = ":";
     while(i < (ValueList.Length())){

         QString current_device = QString(ValueList[i]);
         int from_ = current_device.indexOf(my_operator, 0);
         int to_ = current_device.indexOf(" ", 11);

         int length = to_-from_;

         QString name = current_device.mid(from_+1 , length-1);
         qDebug()<<"vvvvvvvvvvv"<<name;
         qDebug()<<"iiiiiiiiiiiii"<<length;


         qDebug()<<"index of of of <<"<<current_device.indexOf(my_operator, 57);
         qDebug()<<"index of of of <<"<<current_device.indexOf(" ", 68);

         ui->cameras_combo_2->addItem(name);
         i++;
}}

void Widget::on_set_camera_fl_2_clicked()
{


    QString cam_name_fl1 = ui->cameras_combo_2->currentText();

        // QSqlQuery q;
        // q.prepare("UPDATE dynamic_camera SET fl1_camera_name = ? ");
        // q.addBindValue(cam_name_fl1);
        // q.exec();
        // q.first();

        // if(q.exec()){
        //     QMessageBox msg;
        //     msg.setText("Successful");
        //     msg.setWindowTitle("Information");
        //     msg.exec();


        // }

        // ui->cameras_combo_2->clear();

        // camera_slot();
}

void Widget::on_btn_reject_D4_clicked()
{
    if(rejectsystemflag_D4==false){

             rejectsystemflag_D4=true;

            ui->btn_reject_D4->setStyleSheet("border-image: url(:/Image/R1.png);");
        }else{
             rejectsystemflag_D4=false;
             ui->btn_reject_D4->setStyleSheet("border-image: url(:/Image/R2.png);");
    }


    qDebug()<<"rejectsystemflag_D4"<<rejectsystemflag_D4;
}

void Widget::on_btn_reject_D5_clicked()
{
    if(rejectsystemflag_D5==false){

             rejectsystemflag_D5=true;

            ui->btn_reject_D5->setStyleSheet("border-image: url(:/Image/R1.png);");
        }else{
             rejectsystemflag_D5=false;
             ui->btn_reject_D5->setStyleSheet("border-image: url(:/Image/R2.png);");
    }

    qDebug()<<"rejectsystemflag_D5"<<rejectsystemflag_D5;
}

void Widget::on_btn_reject_CL_clicked()
{
    qDebug()<<"in reject off on cl signal";


        if( rejectsystemflag_CL==false){

                 rejectsystemflag_CL=true;

                ui->btn_reject_CL->setStyleSheet("border-image: url(:/Image/R1.png);");
            }else{
                 rejectsystemflag_CL=false;
                 ui->btn_reject_CL->setStyleSheet("border-image: url(:/Image/R2.png);");
        }

        qDebug()<<"rejectsystemflag_CL"<<rejectsystemflag_CL;
}

void Widget::on_FL1_M02_clicked()
{
    FL = 1;
    ui->FL1_M02->resize(148,120);
    ui->FL2_M02->resize(135,109);
}

void Widget::on_FL2_M02_clicked()
{
    CL = 1;
    ui->FL2_M02->resize(148,120);
    ui->FL1_M02->resize(135,109);
}

void Widget::on_Next_M02_clicked()
{
    if(FL==1) {
        if(power_system_flag){
            ui->stackedWidget_3->setCurrentWidget(ui->Mesure04);
            }
        else{
        ui->stackedWidget_3->setCurrentWidget(ui->Mesure05);
            }
        }

    else if(CL==1){
        if(power_system_flag){
            ui->stackedWidget_3->setCurrentWidget(ui->Mesure03);

        }else{
        ui->stackedWidget_3->setCurrentWidget(ui->Mesure06);}
    }
    FL=0;
    CL=0;

    ui->FL2_M02->resize(135,109);
    ui->FL1_M02->resize(135,109);
}

void Widget::on_Cancel_M03_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

}

void Widget::on_Cancel_M03_2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);

}

void Widget::on_Stop_M03_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure06);

    emit(stop_power_system());
}

void Widget::on_Stop_M03_2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure05);

    emit(stop_power_system());
}

void Widget::on_Next_M05_2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure08);


}

void Widget::on_Next_M05_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure07);


}

void Widget::on_Keyboard_RejectSetting_2_clicked()
{
      keyboard = new QProcess(this);
    keyboard->start("FreeVK.exe");

}

void Widget::on_Keyboard_RejectSetting_4_clicked()
{
      keyboard = new QProcess(this);
    keyboard->start("FreeVK.exe");

}

void Widget::on_Next_M07_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure09);
    D4_max_User=ui->lineEdit_D4_max->text().toDouble();
     D4_min_User=ui->lineEdit_D4_min->text().toDouble();
}

void Widget::on_Next_M07_2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure10);
    D5_max_User=ui->lineEdit_D5_max->text().toDouble();
     D5_min_User=ui->lineEdit_D5_min->text().toDouble();

}

void Widget::on_Back_M_FL2_2_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure08);

}

void Widget::on_Done_M_FL2_2_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
    keyboard->close();
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
    QVariantMap data;
    data["pixel_to_mm_max_fl2"] = QString::number(FlPixtoMM2_max);
    data["pixel_to_mm_min_fl2"] = QString::number(FlPixtoMM2_min);



    QString condition = "id = 1";

    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
    Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
}

void Widget::on_StartCalibration_FL2_2_clicked()
{
    ui->StartCalibration_FL2_2->setEnabled(false);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Calibration_Result(HalconCpp::HImage*,double,double,int)),this,SLOT(Mesure_Result2(HalconCpp::HImage*,double,double)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL2Calibration);
}

void Widget::on_Back_M_FL2_3_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->Mesure07);

}

void Widget::on_Done_M_FL2_3_clicked()
{
    ui->settingstackedWidget->setCurrentWidget(ui->SettingStack3);
    ui->stackedWidget_3->setCurrentWidget(ui->MachineSetting);
            keyboard->close();
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);

            QVariantMap data;

            data["pixel_to_mm_max_fl1"] = QString::number(FlPixtoMM1_max);
            data["pixel_to_mm_min_fl1"] = QString::number(FlPixtoMM1_min);


            QString condition = "id = 1";

            Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
            Business_logic_layer->entities.CRUD_machine_setting_db.update(condition,data);
}

void Widget::on_StartCalibration_FL2_3_clicked()
{
    ui->StartCalibration_FL2_3->setEnabled(false);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Calibration_Result(HalconCpp::HImage*,double,double,int)),this,SLOT(Mesure_Result1(HalconCpp::HImage*,double,double)));
    Business_logic_layer->System_Set_Mode(Business_logic::Mode::FL1Calibration);
}

void Widget::on_lineEdit_2_selectionChanged()
{

}

void Widget::on_Test_OS_FL_clicked()
{
    Business_logic_layer->connectionlayer.Camera_Exposure_Setting(Connections::Stations::FL1,ui->EXPOSURE_FL1_lineEdit->text().toDouble());
    Business_logic_layer->connectionlayer.Camera_Exposure_Setting(Connections::Stations::FL2,ui->EXPOSURE_FL2_lineEdit->text().toDouble());
    // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Exposure_fl1",ui->EXPOSURE_FL1_lineEdit->text());
    // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Exposure_fl2",ui->EXPOSURE_FL2_lineEdit->text());
    QVariantMap data;

    data["Exposure_fl1"] = ui->EXPOSURE_FL1_lineEdit->text();
    data["Exposure_fl2"] = ui->EXPOSURE_FL2_lineEdit->text();


    QString condition = "id = 1";


    if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
        qDebug() << "Failed to update machine settings!";
    } else {
        qDebug() << "Machine settings updated successfully!";
    }
}


void Widget::on_Test_OS_CL_clicked()
{
    Business_logic_layer->connectionlayer.Camera_Exposure_Setting(Connections::Stations::CL,ui->EXPOSURE_CL_lineEdit->text().toDouble());
    // Business_logic_layer->entities.CRUD_machine_setting_db.Update("Exposure_fl3",ui->EXPOSURE_CL_lineEdit->text());
    QVariantMap data;

    data["Exposure_fl3"] = ui->EXPOSURE_CL_lineEdit->text();



    QString condition = "id = 1";


    if (!Business_logic_layer->entities.CRUD_machine_setting_db.update(condition, data)) {
        qDebug() << "Failed to update machine settings!";
    } else {
        qDebug() << "Machine settings updated successfully!";
    }

}


void Widget::on_horizontalSlider_exposure_Fl1_sliderMoved(int position)
{
    ui->EXPOSURE_FL1_lineEdit->setText(QString::number(position));
}


void Widget::on_horizontalSlider_exposure_Fl2_sliderMoved(int position)
{
    ui->EXPOSURE_FL2_lineEdit->setText(QString::number(position));
}


void Widget::on_horizontalSlider_exposure_CL_sliderMoved(int position)
{
    ui->EXPOSURE_CL_lineEdit->setText(QString::number(position));
}

