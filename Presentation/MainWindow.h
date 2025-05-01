#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "halconqtwindow.h"
#include "newplotclass.h"
#include"pieview.h"
#include <QMainWindow>
#include <QPieLegendMarker>
#include "widget.h"
#pragma once
#include "Dialog_EnterPassWord.h"

// #include "Dialog_EnterPassWord.h"
// #include "Warning_Dialog.h"
// #include "dongle_ui.h"
// #include "retry_btn.h"
#include <QTimer>
// #include "dongle_class.h"
#include "Report.h"
#include "Business_logic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *myTimer;
    QVector<double> database_vector ;   // read data from machine setting and set it in monitoring
    // Warning_Dialog *dongle_not_connected;
    // dongle_class dongle;
    typedef struct _SHAMSIDATE
    {
        int iYear;
        int iMonth;
        int iDay;
    }SDATE;

    SDATE MiladiToShamsi(int iMiladiMonth,int iMiladiDay,int iMiladiYear);
    int MiladiIsLeap(int miladiYear);

    QTimer *db_timer,*start_timer;

    QDate current_date;
    int fl2_acc , fl2_rej , cl_acc , cl_rej , fl1_rej , fl1_acc;
    double d4_sensitivity ,d5_sensitivity;

    //   Warning_Dialog  * warnin_dialog;
    Dialog_EnterPassWord *enterpassword , *enterpassword2;
    bool powersystemflag;
    bool rejectsystemflag_D4_MainWindow;
    bool rejectsystemflag_D5_MainWindow;
    bool rejectsystemflag_CL_MainWindow;

    QString cam_cl,cam_fl1,cam_fl2;

    QChartView *pie_CL_chartView ;
    QChartView *pie_D5_chartView;
    QChartView *pie_D4_chartView;
    newplotclass *plot_cl;
    QVector<newplotclass*> MaxPlotList;
    QVector<newplotclass*> MinPlotList;
    Widget *settingPage;
    pieview * pie_CL,* pie_D5,* pie_D4;
    QChartView *Statisticview;
    Report *Report_page;
    int  AcceptCount_CL ,RejectCount_CL;
    int FL_CL_arr[6];
    int  AcceptCount_D5 ,RejectCount_D5;
    int  AcceptCount_D4 ,RejectCount_D4;
    double Counter_Reject_CL;
    double Counter_Reject_D5;
    double FlPixtoMM1_max,FlPixtoMM1_min,FlPixtoMM2_max,FlPixtoMM2_min;
    halconqtwindow * OpticSettingCamera1,*OpticSettingCamera2;
    QPieLegendMarker *pieMarker ;
    double threshold_cl_min=0,threshold_cl_max=1,d5=0,D5_Tel=0,D5_Tel_=0,d4=0,D4_Tel=0,D4_Tel_=0;

    ////////////////////////////////////camera
    Business_logic *Business_logic_layer;
    halconqtwindow *centerwindow,* AI_image_CL , * AI_image_FL1,*AI_image_FL2;
    void CustomPlotDraw();
signals :
    void send_change_reject_frame();

    void dev_page_show();
private slots:
    void PreviewImageRecived(HalconCpp::HImage*);
    void on_btn_backtosetting_pressed();

    void on_btn_backtosetting_released();

    void on_btn_power_pressed();

    void on_btn_power_released();

    void on_btn_backtosetting_clicked();

    void on_btn_reset_D5_clicked();

    void on_doubleSpinBox_D4_valueChanged(double arg1);

    void on_btn_save_D5_clicked();

    void on_btn_reset_CL_clicked();

    void on_btn_save_CL_clicked();

    void on_pushButton_clicked();

    void on_btn_reset_D4_clicked();

    void on_btn_Report_D4_clicked();

public slots:

    void receive_rejection();
    void reject_off_on_d4_slot();
    void reject_off_on_d5_slot();
    void reject_off_on_cl_slot();
    void developers_page_show();
    void showmessage();
    void Machine_Setting_Show();
    void on_btn_power_clicked();
    void CL_AI_Result_Recived(HalconCpp::HImage*im,double result,bool flag);
    void FL_AI_Result_Recived(HalconCpp::HImage*im,double minOval,double Maxoval,bool flag,int station);
    void save_pie();
    void getFromWidget();
    void do_lock_screen();
    void query_to_db();
    void Camera_Check_Status_Recived(bool fl1,bool fl2,bool cl);
    void PLC_Check_Status_Recived(bool status);
    // void InitalPLCSetting();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
