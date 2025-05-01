#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QProcess>
#include "halconqtwindow.h"
#include "Business_logic.h"
#include "Dialog_ChangePassWord.h"
#include "Dialog_.h"
#include <QSqlTableModel>
// #include "retry_btn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
using namespace HalconCpp;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QProcess *keyboard;

   Warning_Dialog *warnin_dialog;
    Dialog_ *dialog;
   Dialog_ChangePassWord *changepassword;
   double D4_max_User,D4_min_User,D5_max_User,D5_min_User,FlPixtoMM1_max ,FlPixtoMM1_min,FlPixtoMM2_max,FlPixtoMM2_min;
   bool power_system_flag;
   bool rejectsystemflag_D4;
   bool rejectsystemflag_D5;
   bool rejectsystemflag_CL;
   Business_logic *Business_logic_layer;
   halconqtwindow * OpticSettingCameraCL,*OpticSettingCamera2,*DelaySettingCameraCL,*DelaySettingCamera2,*RejectSettingCamera2 , * DelaySettingCameraCL_2 , * DelaySettingCamera2_2 , * Mesure_CameraCalibration2 , *Mesure_CameraCalibration1;
    int FL,CL;
   void UpdateUIFromDB();
private slots:
void DelaySetting_close();
    void on_Next__SS07_clicked();
    void on_Done_SS01_clicked();


    void on_Next_OS01_clicked();

    void on_Next_OS02_clicked();

    void on_Next_NS01_clicked();

    void on_Next_NS02_clicked();

    void on_Next_ES02_clicked();

    void on_FL2_ES01_clicked();

    void on_Next_ES01_clicked();

    void on_Stop_ES01_clicked();

    void on_Next_ES03_clicked();

    void on_Next_SS01_clicked();

    void on_FL2_SS01_clicked();

    void on_Next_SS02_clicked();

    void on_Stop_SS01_clicked();

    void on_Next_SS05_clicked();


    void on_Back_SS01_clicked();

    void on_Keyboard_DelaySetting_clicked();

    void on_Keyboard_DelaySetting04_clicked();

    void on_Keyboard_DelaySetting03_clicked();

    // void on_Keyboard_DelaySetting02_clicked();

    // void on_Keyboard_Mesure_clicked();

    void on_Keyboard_RejectSetting_clicked();

    void on_Keyboard_NewSample_clicked();

    void on_Keyboard_NS08_clicked();

    void on_Done_NS_clicked();

    void on_Cancel_ES01_clicked();



    void on_DelaySetting_clicked();

    void on_RejectSetting_clicked();

    void on_Mesure_clicked();

    void on_NewSample_clicked();

    void on_EditSample_clicked();

    void on_SampleSelection_clicked();

    void on_Next_NS08_2_clicked();

    void on_Keyboard_EditSample_clicked();

    void on_Keyboard_NS07_3_clicked();

    void on_set_newSample_clicked();

    void on_set_EditSample_clicked();

    void on_sampleName_editSample_comboBox_textActivated(const QString &arg1);

          void on_BacktoMonitoring_btn_clicked();


          void on_sampleSelection_comboBox_textActivated(const QString &arg1);

          void on_CL_OS_clicked();

          void on_FL2_OS_clicked();

          void on_Cancel_OS_FL_clicked();

          void on_Cancel_OS_CL_clicked();

          void on_Next_OS_CL_clicked();

          void on_Next_OS_FL2_clicked();

          void on_Done_OS_FL_clicked();

          void on_Done_OS_CL_clicked();

          void on_Next_DS_clicked();

          void on_CL_DS_clicked();

          void on_FL2_DS_clicked();

          void on_Next_DS_2_clicked();

          void on_Cancel_DS_FL_clicked();

          void on_Cancel_DS_CL_clicked();

          void on_Next_DS_CL_clicked();

          void on_Next_DS_FL_clicked();

          void on_Next_DS_3_clicked();

          void on_Test_DS_FL2_clicked();

          void on_Test_DS_FL_clicked();

          void on_Next_DS_CL_2_clicked();

          void on_Test_DS_CL_clicked();

          void on_Done_DS_FL2_clicked();

          void on_Done_DS_CL_clicked();


          void on_Start_DS_CL_clicked();


          void on_Next_RS01_clicked();

           // void on_Cancel_RS02_clicked();

          void on_Done_RS_clicked();

          void on_Test_RS_clicked();

          void on_Next_M01_clicked();

          void on_Back_M_FL2_clicked();

          void on_Done_M_FL2_clicked();

          void on_Next_RS02_2_clicked();

          void on_Stop_Static_5_clicked();

          void on_Stop_Static_clicked();

          void on_Stop_Static_2_clicked();

          void on_Stop_Static_3_clicked();

          void on_Stop_Static_4_clicked();

          void on_Cancel_RS_clicked();

          void on_Stop_DS_CL_clicked();


          void on_FL2_NS01_clicked();


          void on_Cancel_NS01_clicked();

          void on_Stop_NS01_clicked();


          void on_OpticSetting_clicked();

          void on_Next_NS05_clicked();

          void on_Cancel_SS03_clicked();


          void on_Changepassword_btn_clicked();

          void on_shutdown_clicked();

          void on_shutdown_second_btn_clicked();

          void on_back_to_machine_setting_clicked();
void on_Start_DS_CL_2_clicked();

void on_back_from_devpage_clicked();
void on_set_dongle_clicked();

void on_set_plc_clicked();


void on_fand_connected_cameras_clicked();

void on_cameras_combo_textActivated(const QString &arg1);

void on_set_camera_fl_clicked();

void on_cameras_combo_activated(int index);

void on_find_connected_cameras_cl_3_clicked();

void on_set_camera_cl_clicked();

void on_pushButton_2_clicked();

void on_FL_Camera_Combo_currentIndexChanged(int index);




void on_FL_Camera_Combo_2_currentIndexChanged(int index);

void on_FL_Camera_Combo_3_currentIndexChanged(int index);


void on_FL_Camera_Combo_4_currentIndexChanged(int index);


void on_fand_connected_cameras_2_clicked();

void on_set_camera_fl_2_clicked();

void on_btn_reject_D4_clicked();

void on_btn_reject_D5_clicked();

void on_btn_reject_CL_clicked();


void on_FL1_M02_clicked();

void on_FL2_M02_clicked();

void on_Next_M02_clicked();

void on_Cancel_M03_clicked();

void on_Cancel_M03_2_clicked();

void on_Stop_M03_clicked();

void on_Stop_M03_2_clicked();

void on_Next_M05_2_clicked();

void on_Next_M05_clicked();

void on_Keyboard_RejectSetting_2_clicked();

void on_Keyboard_RejectSetting_4_clicked();

void on_Next_M07_clicked();

void on_Next_M07_2_clicked();

void on_Back_M_FL2_2_clicked();

void on_Done_M_FL2_2_clicked();

void on_StartCalibration_FL2_2_clicked();

void on_Back_M_FL2_3_clicked();

void on_Done_M_FL2_3_clicked();

void on_StartCalibration_FL2_3_clicked();

void on_lineEdit_2_selectionChanged();

void on_Test_OS_FL_clicked();

void on_Test_OS_CL_clicked();

void on_horizontalSlider_exposure_Fl1_sliderMoved(int position);

void on_horizontalSlider_exposure_Fl2_sliderMoved(int position);

void on_horizontalSlider_exposure_CL_sliderMoved(int position);

public slots:


void show_Devpage();
void OpticPreviewImageRecived1(HalconCpp::HImage*);
void OpticPreviewImageRecived2(HalconCpp::HImage*);

void DelayPreviewImageRecived1(HalconCpp::HImage*);
void DelayPreviewImageRecived2(HalconCpp::HImage*);
void RejectTriggerImageCamera2(HalconCpp::HImage*);

void DelayPreviewImageRecived1_2(HalconCpp::HImage*);
void DelayPreviewImageRecived2_2(HalconCpp::HImage*);

void Mesure_Result2(HalconCpp::HImage*,double d5_max,double d5_min);
void Mesure_Result1(HalconCpp::HImage*,double d4_max,double d4_min);


void enable_buttons_slot();

void disable_buttons_slot();

void disable_start_slot();

void enable_start_slot();


signals :

    void set_rejection();
    void set_sensitivity();

    void reject_off_on_cl_signal();

    void reject_off_on_d5_signal();

    void reject_off_on_d4_signal();

    void stop_power_system();

    void set_MainWindow();

    void enable_buttons_signal();

    void disable_buttons_signal();

    void disable_start();
    void enable_start();

    void set_plc_name();

    void set_camera_name();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
