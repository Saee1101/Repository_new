#include "Report.h"
#include "ui_Report.h"
#include <QDebug>



 int ID=0;
 QString name_Product;
 QString date_From;
 QString date_To;
Report::Report(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);


   ui->stackedWidget->setCurrentWidget(ui->page_Report);
    ui->email_address_lbl->setVisible(false);
    ui->email_address_lineEdit->setVisible(false);
    ui->send_report_btn->setVisible(false);
    ui->Product_label->setVisible(false);
    ui->From_label->setVisible(false);
    ui->To_label->setVisible(false);

/////////////////////////////db
     QSqlDatabase db;
    db=QSqlDatabase :: addDatabase("QSQLITE");
    db.setDatabaseName("Pars_Ampoule.db");
    db.open();

    QSqlQuery q;
    for (int i = 0; i < 5; i++) {
        QString tableName = "sample_" + QString::number(i);
        QString queryStr = QString("SELECT value_ FROM %1 WHERE key_ = :key").arg(tableName);


        q.prepare(queryStr);
        q.bindValue(":key", "name");


        if (!q.exec()) {
            qDebug() << "Query failed for table:" << tableName ;
            continue;
        }


        while (q.next()) {
             QString value = q.value(0).toString();
            switch (i) {
            case 0:
                ui->Product_pushButton_1->setText(value);
                database_vector.append(i);
                break;
            case 1:
                ui->Product_pushButton_2->setText(value);
                database_vector.append(i);
                break;
            case 2:
                ui->Product_pushButton_3->setText(value);
                database_vector.append(i);
                break;
            case 3:
                ui->Product_pushButton_4->setText(value);
                database_vector.append(i);
                break;
            case 4:
                ui->Product_pushButton_5->setText(value);
                database_vector.append(i);
                break;
            }
        }
    }
}

Report::~Report()
{
    delete ui;

}

void Report::on_product_btn_clicked()
{
    ui->page_Report->hide();
    ui->stackedWidget->setCurrentWidget(ui->page_Products);
}


void Report::on_from_btn_clicked()
{
ui->page_Report->hide();
ui->stackedWidget->setCurrentWidget(ui->page_From);

}
void Report::on_to_btn_clicked()
{
    ui->page_Report->hide();
    ui->stackedWidget->setCurrentWidget(ui->page_To);
}


void Report::on_Done_btn_clicked()
{
     name_Product=ui->Product_label->text();
     date_From=ui->From_label->text();
     date_To=ui->To_label->text();
//    ui->email_address_lbl->setVisible(true);
//    ui->email_address_lineEdit->setVisible(true);
//    ui->send_report_btn->setVisible(true);
     QStringList Date_From_List=date_From.split(" ");
      qDebug()<<"Date_From_List :"<<Date_From_List;
     QString Date_From_=Date_From_List.at(0);
     QStringList Date_To_List=date_To.split(" ");
     QString Date_To_=Date_To_List.at(0);

     QSqlQuery q;
  q.prepare("SELECT  sum (cl_accepted) , sum (cl_rejected),sum (fl2_accepted),sum (fl2_rejected),sum (fl1_accepted),sum (fl1_rejected)"
            " FROM statistics"
            " WHERE sample_number=? AND  date BETWEEN ? AND ?");
  q.addBindValue(ID);
  q.addBindValue(Date_From_);
  q.addBindValue(Date_To_);
   q.exec();

  QSqlRecord rece = q.record();
  int cl_accepted = rece.indexOf("sum (cl_accepted)"); // index of the field "name"
  int cl_rejected=rece.indexOf("cl_rejected");
 qDebug()<<"q.value(cl_accepted).toInt() :"<<q.value(cl_rejected).toInt();
   /////////////////////////////////////////////////////

//    QString formattedDate =QString::number( sdate.iYear) +"/"+QString::number( sdate.iMonth) +"/"+ QString::number(sdate.iDay);
//        qDebug()<<" SDATEEE :::: "<<sdate.iYear <<"/"<< sdate.iMonth <<"/"<< sdate.iDay;
    QFileDialog dialog;
     QString saveFileName = dialog.getSaveFileName(nullptr,"Save as xlsx","","xlsx Files (*.xlsx)");
     QXlsx::Document xlsx;
     QXlsx::Format format1;
     QXlsx::Format format2;
     QXlsx::Format format3;
      QXlsx::Format format4;
 if((!saveFileName.isEmpty())){
     format1.setPatternBackgroundColor(QColor(Qt::red));
      format1.setFontSize(12);
        format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
       format1.setBorderStyle(QXlsx::Format::BorderThin);

     format2.setPatternBackgroundColor(QColor(Qt::green));
     format2.setFontSize(12);
      format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
      format2.setBorderStyle(QXlsx::Format::BorderThin);

     format3.setFontSize(15);
     format3.setBorderStyle(QXlsx::Format::BorderThin);
           format3.setPatternBackgroundColor(QColor(252,185,51));
           format4.setFontSize(15);
           format4.setBorderStyle(QXlsx::Format::BorderThin);
           xlsx.mergeCells("A1:C1");
           xlsx.setRowHeight(1,40);
           xlsx.setColumnWidth(1,25);
            xlsx.setColumnWidth(2,30);
               xlsx.setColumnWidth(3,30);
           QImage image (":/Image/TivanEX logo.png");
           QImage resizedImage = image.scaled(730, 140, Qt::KeepAspectRatio);
           xlsx.insertImage(0,1,resizedImage);
           xlsx.write(3,1,"Product : " ,format3);
           xlsx.write(4,1,"From : " ,format3);
           xlsx.write(5,1,"To : " ,format3);

              xlsx.write(3,2,name_Product,format3);
              xlsx.write(4,2,date_From,format3);
              xlsx.write(5,2,date_To,format3);

              xlsx.write(3,3,"",format3);
              xlsx.write(4,3,"",format3);
              xlsx.write(5,3,"",format3);

              xlsx.write(7,1,"CL",format4);
              q.first();
              xlsx.write(7,2,q.value("sum (cl_accepted)"),format2);
              xlsx.write(7,3,q.value("sum (cl_rejected)"),format1);

              xlsx.write(8,1,"FL1",format4);

              xlsx.write(8,2,q.value("sum (fl1_accepted)"),format2);
              xlsx.write(8,3,q.value("sum (fl1_rejected)"),format1);

              xlsx.write(9,1,"FL2",format4);

              xlsx.write(9,2,q.value("sum (fl2_accepted)"),format2);
              xlsx.write(9,3,q.value("sum (fl2_rejected)"),format1);
      xlsx.saveAs(saveFileName);
 }
}


void Report::on_Cancel_btn_clicked()
{
ui->page_Report->close();
ID=0;
}


void Report::on_send_report_btn_clicked()
{

}

void Report::on_Form_oK_btn_clicked()
{
    ui->from_btn->setVisible(false);
    ui->From_label->setVisible(true);
    ui->From_label->setText(ui->Year_spinBox->text()+"/"+ui->Month_spinBox->text()+"/"+ui->Day_spinBox->text()
                            +"   "+ui->Hour_spinBox->text()+":"+ui->Minute_spinBox->text()+":"+ui->Second_spinBox->text());


    ui->page_From->close();
    ui->page_Report->show();
}

void Report::on_Product_pushButton_1_clicked()
{
ui->product_btn->setVisible(false);
ui->Product_label->setVisible(true);
ui->Product_label->setText(ui->Product_pushButton_1->text());
ID=database_vector.value(0);
ui->page_Products->close();
ui->page_Report->show();
}

void Report::on_oK_btn_To_clicked()
{
    ui->to_btn->setVisible(false);
    ui->To_label->setVisible(true);
    ui->To_label->setText(ui->Year_spinBox_To->text()+"/"+ui->Month_spinBox_To->text()+"/"+ui->Day_spinBox_To->text()
                          +"   "+ui->Hour_spinBox_To->text()+":"+ui->Minute_spinBox_To->text()+":"+ui->Second_spinBox_To->text());
    ui->page_To->close();
    ui->page_Report->show();
}

void Report::on_Month_spinBox_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Month_spinBox->setPrefix("");
    else if (arg1<10)
        ui->Month_spinBox->setPrefix("0");
}

void Report::on_Day_spinBox_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Day_spinBox->setPrefix("");
    else if (arg1<10)
        ui->Day_spinBox->setPrefix("0");
}

void Report::on_Hour_spinBox_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Hour_spinBox->setPrefix("");
    else if (arg1<10)
        ui->Hour_spinBox->setPrefix("0");
}

void Report::on_Minute_spinBox_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Minute_spinBox->setPrefix("");
    else if (arg1<10)
        ui->Minute_spinBox->setPrefix("0");
}

void Report::on_Second_spinBox_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Second_spinBox->setPrefix("");
    else if (arg1<10)
        ui->Second_spinBox->setPrefix("0");
}

void Report::on_Month_spinBox_To_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Month_spinBox_To->setPrefix("");
    else if (arg1<10)
        ui->Month_spinBox_To->setPrefix("0");
}

void Report::on_Day_spinBox_To_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Day_spinBox_To->setPrefix("");
    else if (arg1<10)
        ui->Day_spinBox_To->setPrefix("0");
}

void Report::on_Hour_spinBox_To_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Hour_spinBox_To->setPrefix("");
    else if (arg1<10)
        ui->Hour_spinBox_To->setPrefix("0");
}

void Report::on_Minute_spinBox_To_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Minute_spinBox_To->setPrefix("");
    else if (arg1<10)
        ui->Minute_spinBox_To->setPrefix("0");
}

void Report::on_Second_spinBox_To_valueChanged(int arg1)
{
    if(arg1>9)
    ui->Second_spinBox_To->setPrefix("");
    else if (arg1<10)
        ui->Second_spinBox_To->setPrefix("0");
}

void Report::on_Product_pushButton_2_clicked()
{
    ui->product_btn->setVisible(false);
    ui->Product_label->setVisible(true);
    ui->Product_label->setText(ui->Product_pushButton_2->text());
    ID=database_vector.value(1);
    ui->page_Products->close();
    ui->page_Report->show();
}

void Report::on_Product_pushButton_3_clicked()
{
    ui->product_btn->setVisible(false);
    ui->Product_label->setVisible(true);
    ui->Product_label->setText(ui->Product_pushButton_3->text());
    ID=database_vector.value(2);
    ui->page_Products->close();
    ui->page_Report->show();
}

void Report::on_Product_pushButton_4_clicked()
{
    ui->product_btn->setVisible(false);
    ui->Product_label->setVisible(true);
    ui->Product_label->setText(ui->Product_pushButton_4->text());
    ID=database_vector.value(3);
    ui->page_Products->close();
    ui->page_Report->show();
}

void Report::on_Product_pushButton_5_clicked()
{
    ui->product_btn->setVisible(false);
    ui->Product_label->setVisible(true);
    ui->Product_label->setText(ui->Product_pushButton_5->text());
    ID=database_vector.value(4);
    ui->page_Products->close();
    ui->page_Report->show();
}

void Report::on_Product_pushButton_6_clicked()
{
    ui->product_btn->setVisible(false);
    ui->Product_label->setVisible(true);
    ui->Product_label->setText(ui->Product_pushButton_6->text());
    ID=database_vector.value(5);
    ui->page_Products->close();
    ui->page_Report->show();
}
