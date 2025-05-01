#ifndef REPORT_H
#define REPORT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFileDialog>
#include <Business_logic.h>
#include "xlsxdocument.h"
namespace Ui {
class Report;
}

class Report : public QWidget
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();
 QVector<int> database_vector ;
    Business_logic *Business_logic_layer;
private slots:
    void on_product_btn_clicked();

    void on_from_btn_clicked();

    void on_to_btn_clicked();

    void on_Done_btn_clicked();

    void on_Cancel_btn_clicked();

    void on_send_report_btn_clicked();

    void on_Form_oK_btn_clicked();

    void on_Product_pushButton_1_clicked();

    void on_oK_btn_To_clicked();

    void on_Month_spinBox_valueChanged(int arg1);

    void on_Day_spinBox_valueChanged(int arg1);

    void on_Hour_spinBox_valueChanged(int arg1);

    void on_Minute_spinBox_valueChanged(int arg1);

    void on_Second_spinBox_valueChanged(int arg1);

    void on_Month_spinBox_To_valueChanged(int arg1);

    void on_Day_spinBox_To_valueChanged(int arg1);

    void on_Hour_spinBox_To_valueChanged(int arg1);

    void on_Minute_spinBox_To_valueChanged(int arg1);

    void on_Second_spinBox_To_valueChanged(int arg1);

    void on_Product_pushButton_2_clicked();

    void on_Product_pushButton_3_clicked();

    void on_Product_pushButton_4_clicked();

    void on_Product_pushButton_5_clicked();

    void on_Product_pushButton_6_clicked();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
