#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QtCore>
#include <QVector>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPrinter>
#include <QImage>
#include <QTimer>
#include <QDate>


int static cl_stage = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTimer = new QTimer;
    db_timer = new QTimer;
    start_timer = new QTimer;

    // dongle_not_connected = new Warning_Dialog(this);
   d4_sensitivity = 0.0;
   d5_sensitivity = 0.0;

   powersystemflag = false;
   rejectsystemflag_D4_MainWindow = false;
   rejectsystemflag_CL_MainWindow=false;
   rejectsystemflag_D5_MainWindow=false;



    Business_logic_layer = new Business_logic(this);
    connect(Business_logic_layer,SIGNAL(BusinessLogic_Camera_Connection_Status(bool,bool,bool))
            ,this,SLOT(Camera_Check_Status_Recived(bool,bool,bool)));
    // connect(Business_logic_layer,SIGNAL(BusinessLogic_PLC_Connection_Status(bool))
    //         ,this,SLOT(PLC_Check_Status_Recived(bool)));
    Business_logic_layer->CheckSystem_Connection_Status();
    settingPage = new Widget(this);
    settingPage->hide();
    settingPage->Business_logic_layer=Business_logic_layer;
    settingPage->power_system_flag = powersystemflag;

    receive_rejection();
connect(settingPage,SIGNAL(reject_off_on_cl_signal()),this,SLOT(reject_off_on_cl_slot()));
connect(settingPage,SIGNAL(reject_off_on_d5_signal()),this,SLOT(reject_off_on_d5_slot()));
connect(settingPage,SIGNAL(reject_off_on_d4_signal()),this,SLOT(reject_off_on_d4_slot()));
connect(settingPage,SIGNAL(stop_power_system()),this,SLOT(on_btn_power_clicked()));
connect(settingPage,SIGNAL(set_MainWindow()),this,SLOT(getFromWidget()));
//connect(myTimer,SIGNAL(timeout()),this,SLOT(showmessage()));
connect(db_timer,SIGNAL(timeout()),this,SLOT(query_to_db()));
// connect(this,SIGNAL(dev_page_show()),settingPage,SLOT(show_Devpage()));
connect(settingPage,SIGNAL(set_sensitivity()),this,SLOT(receive_sensitivity()));
connect(settingPage,SIGNAL(set_rejection()),this,SLOT(receive_rejection()));
connect(Business_logic_layer,SIGNAL(BusinessLogic_CL_Inpection_Result(HalconCpp::HImage*,double,bool)),this
        ,SLOT(CL_AI_Result_Recived(HalconCpp::HImage*,double,bool)));
connect(Business_logic_layer,SIGNAL(BusinessLogic_Inpection_Result(HalconCpp::HImage*,double,
                                                                    double,bool,int)),this
        ,SLOT(FL_AI_Result_Recived(HalconCpp::HImage*,double,
                                  double,bool,int)));
db_timer->start(1*60*1000);

AI_image_CL = new halconqtwindow(this);
AI_image_FL1 = new halconqtwindow(this);
AI_image_FL2 = new halconqtwindow(this);
AI_image_FL1->openwindow(200,200);
AI_image_FL2->openwindow(200,200);
AI_image_CL->openwindow(200,200);
ui->Camera_Layout_CL->addWidget(AI_image_CL);
ui->Camera_Layout_D4->addWidget(AI_image_FL1);
ui->Camera_Layout_D5->addWidget(AI_image_FL2);
//myTimer->start(300000);
//myTimer->start(3000);
// connect(dongle_not_connected,SIGNAL(accepted()),this,SLOT(showmessage()));
//connect(dongle,SIGNAL(lock_screen()),this,SLOT(do_lock_screen()));
//connect(enterpassword,SIGNAL(Widget_Show()),this,SLOT(Machine_Setting_Show()));
//    settingPage->showFullScreen();
///////////////////////////////////////////////////setparameter
    powersystemflag=false;
    CustomPlotDraw();

    pie_CL = new pieview;
    pie_D5 = new pieview;
    pie_D4=new pieview;

     pie_CL_chartView= new QChartView(pie_CL);
     pie_D5_chartView = new QChartView(pie_D5);
     pie_D4_chartView=new QChartView(pie_D4);
//    Statisticview = pie_CL_chartView;
    //************ PIE VIEW **************//
    AcceptCount_CL = 1;
    RejectCount_CL = 1;
    AcceptCount_D5 = 1;
    RejectCount_D5 = 1;
    AcceptCount_D4 = 1;
    RejectCount_D4 = 1;
    pie_CL_chartView->setRenderHint(QPainter::Antialiasing);
    ui->Statistic_MonitorLayout_CL->addWidget(pie_CL_chartView);
   pie_CL_chartView->setBackgroundBrush(QBrush(QColor(44,44,44)));

  pie_D5_chartView->setRenderHint(QPainter::Antialiasing);
   ui->Statistic_MonitorLayout_D5->addWidget(pie_D5_chartView);
  pie_D5_chartView->setBackgroundBrush(QBrush(QColor(44,44,44)));

  pie_D4_chartView->setRenderHint(QPainter::Antialiasing);
   ui->Statistic_MonitorLayout_D4->addWidget(pie_D4_chartView);
  pie_D4_chartView->setBackgroundBrush(QBrush(QColor(44,44,44)));

  pie_CL->series->slices().at(0)->setValue(AcceptCount_CL);
   pie_CL->series->slices().at(1)->setValue(RejectCount_CL);
   pie_CL->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_CL));
   pie_CL->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_CL));

   pie_D5->series->slices().at(0)->setValue(AcceptCount_D5);
    pie_D5->series->slices().at(1)->setValue(RejectCount_D5);
    pie_D5->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_D5));
   pie_D5->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_D5));

   pie_D4->series->slices().at(0)->setValue(AcceptCount_D4);
    pie_D4->series->slices().at(1)->setValue(RejectCount_D4);
    pie_D4->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_D4));
   pie_D4->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_D4));

   start_timer->start(5*1000);

}
void MainWindow::PreviewImageRecived(HalconCpp::HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    centerwindow->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(centerwindow->WinfoeID());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::reject_off_on_d4_slot()
{
  //  qDebug()<<"in reject off on d4 slot";

    if(rejectsystemflag_D4_MainWindow==false){
        rejectsystemflag_D4_MainWindow = true;
    }
    else{
        rejectsystemflag_D4_MainWindow = false;
    }
}

void MainWindow::reject_off_on_d5_slot()
{


   // qDebug()<<"in reject off on d5 slot";

    if(rejectsystemflag_D5_MainWindow==false){
        rejectsystemflag_D5_MainWindow = true;
    }
    else{
        rejectsystemflag_D5_MainWindow = false;
    }
}

void MainWindow::reject_off_on_cl_slot()
{
 //   qDebug()<<"in reject off on cl slot";

    if(rejectsystemflag_CL_MainWindow==false){
        rejectsystemflag_CL_MainWindow = true;
    }
    else{
        rejectsystemflag_CL_MainWindow = false;
    }
}

void MainWindow::on_btn_backtosetting_pressed()
{
    //ui->btn_backtosetting->setGeometry(ui->btn_backtosetting->x()-1,ui->btn_backtosetting->y()+3,ui->btn_backtosetting->width()-2,ui->btn_backtosetting->height()-2);
    ui->btn_backtosetting->setGeometry(ui->btn_backtosetting->x(),ui->btn_backtosetting->y(),ui->btn_backtosetting->width()-2,ui->btn_backtosetting->height()-2);
}

void MainWindow::on_btn_backtosetting_released()
{
    //ui->btn_backtosetting->setGeometry(ui->btn_backtosetting->x()+1,ui->btn_backtosetting->y()-3,ui->btn_backtosetting->width()+2,ui->btn_backtosetting->height()+2);
    ui->btn_backtosetting->setGeometry(ui->btn_backtosetting->x(),ui->btn_backtosetting->y(),ui->btn_backtosetting->width()+2,ui->btn_backtosetting->height()+2);
}
////////////////////// btn_power_clicked
void MainWindow::on_btn_power_clicked()
{

    if(powersystemflag==false){

            powersystemflag=true;
        qDebug()<<"buttom cliked";
            ui->btn_power->setStyleSheet("border-image: url(:/Image/System Control On.png);");
        Business_logic_layer->System_Set_Mode(Business_logic::Mode::Inspection);
        }else{
            qDebug()<<"buttom uncliked";
            powersystemflag=false;
            Business_logic_layer->System_Set_Mode(Business_logic::Mode::systemOff);
            ui->btn_power->setStyleSheet("border-image: url(:/Image/System Control Off.png);");
        }
        settingPage->power_system_flag=powersystemflag;
        emit(send_change_reject_frame());
}



void MainWindow::on_btn_power_pressed()
{
    ui->btn_power->setGeometry(ui->btn_power->x(),ui->btn_power->y(),ui->btn_power->width()-2,ui->btn_power->height()-2);

}

void MainWindow::on_btn_power_released()
{
    ui->btn_power->setGeometry(ui->btn_power->x(),ui->btn_power->y(),ui->btn_power->width()+2,ui->btn_power->height()+2);
}

/////////////////////////////////////////////////////////////////

void MainWindow::on_btn_backtosetting_clicked()
{
    enterpassword=new Dialog_EnterPassWord(this);
    enterpassword->is_operator = true;

     // enterpassword->current_password=Business_logic_layer->entities.CRUD_user_db.readByUsername("admin").password;

     User user = Business_logic_layer->entities.CRUD_user_db.readByField("user_name", "admin");
     enterpassword->current_password=user.password;
    connect(enterpassword,SIGNAL(Widget_Show()),this,SLOT(Machine_Setting_Show()));

    enterpassword->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );
    enterpassword->setGeometry(390,370,390,247);
        enterpassword->show();





    // Machine_Setting_Show();
}

void MainWindow::on_btn_reset_D5_clicked()
{

 ui->label_D5_Accept_num->clear();
 ui->label_D5_Reject_num->clear();
    AcceptCount_D5=1;
    RejectCount_D5=1;


    pie_D5->series->slices().at(0)->setValue(AcceptCount_D5);
     pie_D5->series->slices().at(1)->setValue(RejectCount_D5);
     pie_D5->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_D5));
    pie_D5->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_D5));


}



void MainWindow::on_doubleSpinBox_D4_valueChanged(double arg1)
{

}
///////////////////////////////////////

void MainWindow::CL_AI_Result_Recived(HalconCpp::HImage*im,double result,bool flag)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    AI_image_CL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
        im->DispImage(AI_image_CL->WinfoeID());
            plot_cl->setData(result);
           if(flag)
            {
               AcceptCount_CL++;
               // FL_CL_arr[3]++;
               ui->label_CL_Accept_num->clear();
               ui->label_CL_Accept_num->setText(QString::number(AcceptCount_CL));
             pie_CL->series->slices().at(0)->setValue(AcceptCount_CL);
            }
           else
            {
               if(result<threshold_cl_min&&result>=0.0)
               {
                           RejectCount_CL++;
                           // FL_CL_arr[2]++;
                           ui->label_CL_Reject_num->clear();
                           ui->label_CL_Reject_num->setText(QString::number(RejectCount_CL));
                             pie_CL->series->slices().at(1)->setValue(RejectCount_CL);
               }
            }
}

void MainWindow::FL_AI_Result_Recived(HalconCpp::HImage*im,double Minoval,double Maxoval,bool flag,int station)
{
    int *acceptcounter ,*rejectcounter;
    QLabel* LabelAccept,*LabelReject;
    pieview* pie;
    halconqtwindow *window;
    if(station){
        acceptcounter=&AcceptCount_D4;
        rejectcounter=&RejectCount_D4;
        LabelAccept= ui->label_D4_Accept_num;
        LabelReject =ui->label_D4_Reject_num;
        pie=pie_D4;
        window=AI_image_FL2;
    }else{
        acceptcounter=&AcceptCount_D5;
        rejectcounter=&RejectCount_D5;
        LabelAccept= ui->label_D5_Accept_num;
        LabelReject =ui->label_D5_Reject_num;
        pie=pie_D5;
        window=AI_image_FL1;
    }

    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    window->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    if(*im->CountChannels().ToDArr()>2)
    im->DispColor( window->WinfoeID());
    else
       im->DispImage(window->WinfoeID());

    MaxPlotList[station]->setData(Maxoval);
    MinPlotList[station]->setData(Minoval);
    if (flag)
    {
        *acceptcounter= *acceptcounter+1;
        LabelAccept->clear();
        LabelAccept->setText(QString::number(*acceptcounter));
        pie->series->slices().at(0)->setValue(*acceptcounter);
    }
    else
    {
        if(Maxoval>2)
        {
            *rejectcounter=*rejectcounter+1;
            LabelReject->clear();
            LabelReject->setText(QString::number(*rejectcounter));
            pie->series->slices().at(1)->setValue(*rejectcounter);
        }

    }

}
void MainWindow::Machine_Setting_Show()
{

    settingPage->showFullScreen();
    settingPage->UpdateUIFromDB();
}


void MainWindow::save_pie()
{
    QScreen* screen = QApplication::primaryScreen();
    QPixmap ChartImage = screen->grabWindow(Statisticview->winId());
     QFileDialog dialog;

     QString saveFileName = dialog.getSaveFileName(nullptr,"Save as PDF","","PDF Files (*.pdf)");

     if((!saveFileName.isEmpty())){
         QPdfWriter pdfWriter(saveFileName);
         pdfWriter.setPageSize(QPageSize(QPageSize::A5));
         pdfWriter.setPageOrientation(QPageLayout::Landscape);
         pdfWriter.setResolution(300);
         QPainter pdfPainter(&pdfWriter);
         pdfPainter.drawPixmap(0,0,pdfWriter.width(),pdfWriter.height() , ChartImage);
         pdfPainter.end();
     }
}

void MainWindow::getFromWidget()
{
    CustomPlotDraw();
// ui->gridLayout_D5_max->removeWidget(plot_d5_max);
// plot_d5_max=new newplotclass;
//        plot_d5_max->setparameter(580,190,21,5,d5,d5+D5_Tel,d5-D5_Tel_);
// ui->gridLayout_D5_max->addWidget(plot_d5_max);

// ui->gridLayout_D5_max->removeWidget(plot_d5_min);
// plot_d5_min=new newplotclass;
//        plot_d5_min->setparameter(580,190,21,5,d5,d5+D5_Tel,d5-D5_Tel_);
// //ui->gridLayout_D5_min->addWidget(plot_d5_min);

// ui->gridLayout_D4_max->removeWidget(plot_d4_max);
// plot_d4_max=new newplotclass;
//        plot_d4_max->setparameter(580,190,21,5,d4,d4+D4_Tel,d4-D4_Tel_);
// ui->gridLayout_D4_max->addWidget(plot_d4_max);

// //ui->gridLayout_D4_min->removeWidget(plot_d4_min);
// plot_d4_min=new newplotclass;
//        plot_d4_min->setparameter(580,190,21,5,d4,d4+D4_Tel,d4-D4_Tel_);
// //ui->gridLayout_D4_min->addWidget(plot_d4_min);

//    ui->gridLayout_CL->removeWidget(plot_cl);
//  plot_cl= new newplotclass;
//        plot_cl->setparameter(580,190,21,5,(threshold_cl_min+threshold_cl_max)/2,threshold_cl_max,threshold_cl_min);
// ui->gridLayout_CL->addWidget(plot_cl);





//        d4_sensitivity=database_vector.value(15);
//               d5_sensitivity=database_vector.value(11);


}

void MainWindow::do_lock_screen()
{
    QWidget::setDisabled(true);
}

void MainWindow::query_to_db()
{

    current_date = QDate::currentDate();
    SDATE sdate = MiladiToShamsi(current_date.month(),current_date.day(),current_date.year());

    QDateTime time = QDateTime::currentDateTime();

    QString hourTime = time.toString("hh");
    QString minuteTime = time.toString("mm");
    QString formated_day {sdate.iDay >= 1 && sdate.iDay < 10 ? "/0"+QString::number(sdate.iDay) :
                                                                   "/"+QString::number(sdate.iDay)};
  QString formated_month {sdate.iMonth >= 1 && sdate.iMonth < 10 ? "/0"+QString::number(sdate.iMonth) :
                                                                      "/"+QString::number(sdate.iMonth)};
    QString formatedDate = QString::number(sdate.iYear)+formated_month+formated_day;

    fl2_rej = FL_CL_arr[0]; //FL2 rejected
    fl2_acc = FL_CL_arr[1]; //FL2 accepted
    cl_rej = FL_CL_arr[2]; //CL rejected
    cl_acc = FL_CL_arr[3]; //CL accepted
    fl1_rej = FL_CL_arr[4]; //FL1 rejected
    fl1_acc = FL_CL_arr[5]; //FL1 accepted

    QSqlDatabase db;
    db=QSqlDatabase :: addDatabase("QSQLITE");
    db.setDatabaseName("ParsAmpoule_P3.db");
    QSqlQuery q;

    if(db.open()){


        qDebug()<<"in db open";

        q.prepare("INSERT INTO statistics(date,hour,minute,cl_accepted,cl_rejected,fl2_accepted,fl2_rejected,fl1_rejected,fl1_accepted,sample_id) VALUES(:Date , :Hour , :Minute ,:CL_acc , :CL_rej , :FL2_acc , :FL2_rej, :FL1_acc , :FL1_rej,:sample_number)");

        q.bindValue(":Date",formatedDate);
        q.bindValue(":Hour",hourTime);
        q.bindValue(":Minute",minuteTime);
        q.bindValue(":CL_acc",cl_acc);
        q.bindValue(":CL_rej",cl_rej);
        q.bindValue(":FL2_acc",fl2_acc);
        q.bindValue(":FL2_rej",fl2_rej);
        q.bindValue(":FL1_rej",fl1_acc);
        q.bindValue(":FL1_acc",fl1_rej);
        // q.bindValue(":sample_number",Business_logic_layer->entities.CRUD_user_db.readByUsername("sample_number").id);
        // Statistics user = Business_logic_layer->entities.CRUD_user_db.readByField("sample_id", "sample_number");
        // enterpassword->current_password=user.password;
        // q.bindValue(":sample_number",database_vector.value(12));
    FL_CL_arr[0]=0; //FL2 rejected
    FL_CL_arr[1]=0; //FL2 accepted
    FL_CL_arr[2]=0; //CL rejected
    FL_CL_arr[3]=0; //CL accepted
    FL_CL_arr[4]=0; //FL1 rejected
    FL_CL_arr[5]=0; //FL1 accepted

}
}

void MainWindow::Camera_Check_Status_Recived(bool fl1, bool fl2, bool cl)
{
    QString status;
    status = QString::number(fl1)+"وضعیت دوربین FL1" + "\n"+
            QString::number(fl2)+ "وضعیت دوربین FL2" + "\n"+
             QString::number(cl)+ "وضعیت دوربین CL";
    QMessageBox messageBox(QMessageBox::Critical,
                           "WARNING!",
                           status,
                           QMessageBox::Retry |QMessageBox::Ignore,
                           this);

    if (messageBox.exec() == QMessageBox::Retry) {
        Business_logic_layer->CheckSystem_Connection_Status();
    }else{
        Business_logic_layer->Initial_System();
    }
}

void MainWindow::PLC_Check_Status_Recived(bool status)
{
    QMessageBox messageBox(QMessageBox::Critical,
                           "WARNING!",
                           "پی ال سی متصل نیست",
                           QMessageBox::Retry |QMessageBox::Discard,
                           this);

    if (messageBox.exec() == QMessageBox::Retry) {
        Business_logic_layer->CheckSystem_Connection_Status();
    }else{
        MainWindow:: ~MainWindow();
    }
}

void MainWindow::on_btn_reset_CL_clicked()
{
    ui->label_CL_Reject_num->clear();
    ui->label_CL_Accept_num->clear();

    AcceptCount_CL=1;
    RejectCount_CL=1;
    pie_CL->series->slices().at(0)->setValue(AcceptCount_CL);
     pie_CL->series->slices().at(1)->setValue(RejectCount_CL);
     pie_CL->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_CL));
   pie_CL->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_CL));
}

void MainWindow::on_btn_save_CL_clicked()
{
Report_page =new Report(this);
Report_page->show();
Report_page->move(260,200);
}
void MainWindow::on_btn_Report_D4_clicked()
 {
    Report_page =new Report(this);
    Report_page->show();
    Report_page->move(260,200);

 }

void MainWindow::on_btn_save_D5_clicked()
  {
    Report_page =new Report(this);
    Report_page->show();
    Report_page->move(260,200);
 }

void MainWindow::showmessage()
{
    // if(dongle.run_lock()==100){

    //     ui->btn_power->setEnabled(true);
    //     ui->btn_backtosetting->setEnabled(true);
    //  }
    // else{

    //     dongle_not_connected->setObjectName("dongle_not_connected");
    //     dongle_not_connected->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    //     dongle_not_connected->setGeometry(90,370,1030,247);
    //     dongle_not_connected->setStyleSheet("#dongle_not_connected{background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 28.png);}");
    //     dongle_not_connected->show();

    //     ui->btn_power->setEnabled(false);
    //     ui->btn_backtosetting->setEnabled(false);

    //     if(powersystemflag){
    //         on_btn_power_clicked();
    //     }


    // }
}


MainWindow::SDATE MainWindow::MiladiToShamsi(int iMiladiMonth, int iMiladiDay, int iMiladiYear)
{
    int  shamsiDay, shamsiMonth, shamsiYear;
    int  dayCount,farvardinDayDiff,deyDayDiff ;
    int  sumDayMiladiMonth[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    int  sumDayMiladiMonthLeap[]= {0,31,60,91,121,152,182,213,244,274,305,335};
    SDATE  shamsidate;

 farvardinDayDiff=79;

if (MiladiIsLeap(iMiladiYear))
 {
    dayCount = sumDayMiladiMonthLeap[iMiladiMonth-1] + iMiladiDay;
 }
else
 {
    dayCount = sumDayMiladiMonth[iMiladiMonth-1] + iMiladiDay;
 }
if((MiladiIsLeap(iMiladiYear - 1)))
 {
    deyDayDiff = 11;
 }
else
 {
    deyDayDiff = 10;
 }
if (dayCount > farvardinDayDiff)
{
    dayCount = dayCount - farvardinDayDiff;
    if (dayCount <= 186)
     {
      switch (dayCount%31)
       {
    case 0:
     shamsiMonth = dayCount / 31;
     shamsiDay = 31;
    break;
    default:
     shamsiMonth = (dayCount / 31) + 1;
     shamsiDay = (dayCount%31);
    break;
      }
      shamsiYear = iMiladiYear - 621;
     }
   else
     {
    dayCount = dayCount - 186;
    switch (dayCount%30)
      {
       case 0:
    shamsiMonth = (dayCount / 30) + 6;
    shamsiDay = 30;
       break;
     default:
       shamsiMonth = (dayCount / 30) + 7;
       shamsiDay = (dayCount%30);
       break;
     }
      shamsiYear = iMiladiYear - 621;
    }
  }
else
  {
    dayCount = dayCount + deyDayDiff;

    switch (dayCount%30)
    {
    case 0 :
      shamsiMonth = (dayCount / 30) + 9;
      shamsiDay = 30;
     break;
    default:
      shamsiMonth = (dayCount / 30) + 10;
      shamsiDay = (dayCount%30);
     break;
    }
    shamsiYear = iMiladiYear - 622;

  }
    shamsidate.iYear = shamsiYear;
    shamsidate.iMonth = shamsiMonth;
    shamsidate.iDay = shamsiDay;
    return  shamsidate;
}

int MainWindow::MiladiIsLeap(int miladiYear)
{
    if(((miladiYear % 100)!= 0 && (miladiYear % 4) == 0) || ((miladiYear % 100)== 0 && (miladiYear % 400) == 0))
      return 1;
    else
      return 0;
}

void MainWindow::on_pushButton_clicked()
{
//     enterpassword2=new Dialog_EnterPassWord(this);
//     enterpassword2->is_operator = false;
//     enterpassword2->set_echoMode();
//     connect(enterpassword2,SIGNAL(Widget_Show()),this,SLOT(developers_page_show()));

//     enterpassword2->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );
//     enterpassword2->setGeometry(390,370,390,247);
// //    enterpassword->setGeometry(390,370,400,280);
//         enterpassword2->show();

}

void MainWindow::receive_rejection()
{

        // QSqlDatabase db;
        // db=QSqlDatabase :: addDatabase("QSQLITE");
        // db.setDatabaseName("ParsAmpoule_P3.db");
        // db.open();

        // QSqlQuery query;

        //  query.exec();
        //  query.prepare("SELECT cl_reject_status , fl1_reject_status , fl2_reject_status from machine_setting");
        //  query.exec();
        //  query.first();
        //  rejectsystemflag_CL_MainWindow = query.value("cl_reject_status").toBool();
        //  qDebug()<<"rejectsystemflag_CL_MainWindow"<<rejectsystemflag_CL_MainWindow;
        //  rejectsystemflag_D4_MainWindow = query.value("fl1_reject_status").toBool();
        //  qDebug()<<"rejectsystemflag_D4_MainWindow"<<rejectsystemflag_D4_MainWindow;
        //  rejectsystemflag_D5_MainWindow = query.value("fl2_reject_status").toBool();
        //  qDebug()<<"rejectsystemflag_D5_MainWindow"<<rejectsystemflag_D5_MainWindow;


        //  query.exec();

        //  if(!query.exec()){
        //      qDebug()<<query.lastError().text();
        //  }

        //         switch (rejectsystemflag_CL_MainWindow) {
        //         case 0 :
        //  ui->label_CL_Reject->setStyleSheet("border-image: url(:/Image/CL-R-OFF.png);");
        //             break;
        //         case 1 :
        //             ui->label_CL_Reject->setStyleSheet("border-image: url(:/Image/CL-R-ON.png);");
        //             break;

        //         }
        //         switch (rejectsystemflag_D4_MainWindow) {
        //         case 0 :
        // ui->label_FL1_Reject->setStyleSheet("border-image: url(:/Image/FL1-R-OFF.png);");
        //             break;
        //         case 1 :
        //            ui->label_FL1_Reject->setStyleSheet("border-image: url(:/Image/FL1-R-ON.png);");
        //             break;

        //         }
        //         switch (rejectsystemflag_D5_MainWindow) {
        //         case 0 :
        // ui->label_FL2_Reject->setStyleSheet("border-image: url(:/Image/FL2-R-OFF.png);");
        //             break;
        //         case 1 :
        //            ui->label_FL2_Reject->setStyleSheet("border-image: url(:/Image/FL2-R-ON.png);");
        //             break;

        //         }
}


void MainWindow::developers_page_show()
{
    // settingPage->showFullScreen();
    emit(dev_page_show());
}

void MainWindow::on_btn_reset_D4_clicked()
{
    ui->label_D4_Accept_num->clear();
    ui->label_D4_Reject_num->clear();
       AcceptCount_D4=1;
       RejectCount_D4=1;
       pie_D4->series->slices().at(0)->setValue(AcceptCount_D4);
        pie_D4->series->slices().at(1)->setValue(RejectCount_D4);
        pie_D4->series->slices().at(0)->setLabel("Acc : "+QString::number(AcceptCount_D4));
       pie_D4->series->slices().at(1)->setLabel("Rej : "+QString::number(RejectCount_D4));
}

void MainWindow::CustomPlotDraw()
{
    Business_logic_layer->entities.loadData();
    if(!ui->gridLayout_CL->isEmpty()){
        ui->gridLayout_CL->removeWidget(plot_cl);
        ui->gridLayout_D4_max->removeWidget(MaxPlotList[0]);
        ui->gridLayout_D4_min->removeWidget(MinPlotList[0]);
        ui->gridLayout_D5_max->removeWidget(MaxPlotList[1]);
        ui->gridLayout_D5_min->removeWidget(MinPlotList[1]);
    }
    plot_cl= new newplotclass;
    plot_cl->setparameter(580,190,21,5,(Business_logic_layer->entities.dataMap_machine_setting_db.value("cl_stage").toDouble()+1)/2,1
                          ,Business_logic_layer->entities.dataMap_machine_setting_db.value("cl_stage").toDouble());
    ui->gridLayout_CL->addWidget(plot_cl);


    MaxPlotList.resize(2);
    MinPlotList.resize(2);
    for(int i=0;i<2;i++){
        MaxPlotList[i]=new newplotclass;
        MinPlotList[i]=new newplotclass;
    }
    double FL1_min=Business_logic_layer->entities.dataMap_sample_db.value("diamiter_min_fl1").toDouble();
    double FL1_max=Business_logic_layer->entities.dataMap_sample_db.value("diamiter_max_fl1").toDouble();
    double FL2_min=Business_logic_layer->entities.dataMap_sample_db.value("diamiter_min_fl2").toDouble();
    double FL2_max=Business_logic_layer->entities.dataMap_sample_db.value("diamiter_max_fl2").toDouble();
    MaxPlotList[0]->setparameter(580,99,21,5,(FL1_max+FL1_min)/2,FL1_max,FL1_min);
    ui->gridLayout_D4_max->addWidget(MaxPlotList[0]);

    MinPlotList[0]->setparameter(580,99,21,5,(FL1_max+FL1_min)/2,FL1_max,FL1_min);
        ui->gridLayout_D4_min->addWidget(MinPlotList[0]);
    MaxPlotList[1]->setparameter(580,99,21,5,(FL2_max+FL2_min)/2,FL2_max,FL2_min);
    ui->gridLayout_D5_max->addWidget(MaxPlotList[1]);
    MinPlotList[1]->setparameter(580,99,21,5,(FL2_max+FL2_min)/2,FL2_max,FL2_min);
       ui->gridLayout_D5_min->addWidget(MinPlotList[1]);
    ui->label_Sample_Name->setText(Business_logic_layer->entities.dataMap_sample_db.value("name"));



    switch (Business_logic_layer->entities.dataMap_machine_setting_db.value("cl_reject_status").toInt()) {
                case 0 :
         ui->label_CL_Reject->setStyleSheet("border-image: url(:/Image/CL-R-OFF.png);");
                    break;
                case 1 :
                    ui->label_CL_Reject->setStyleSheet("border-image: url(:/Image/CL-R-ON.png);");
                    break;

                }
                switch (Business_logic_layer->entities.dataMap_machine_setting_db.value("fl1_reject_status").toInt()) {
                case 0 :
        ui->label_FL1_Reject->setStyleSheet("border-image: url(:/Image/FL1-R-OFF.png);");
                    break;
                case 1 :
                   ui->label_FL1_Reject->setStyleSheet("border-image: url(:/Image/FL1-R-ON.png);");
                    break;

                }
                switch (Business_logic_layer->entities.dataMap_machine_setting_db.value("fl2_reject_status").toInt()) {
                case 0 :
        ui->label_FL2_Reject->setStyleSheet("border-image: url(:/Image/FL2-R-OFF.png);");
                    break;
                case 1 :
                   ui->label_FL2_Reject->setStyleSheet("border-image: url(:/Image/FL2-R-ON.png);");
                    break;

                }


}
