#ifndef DIALOG_ENTERPASSWORD_H
#define DIALOG_ENTERPASSWORD_H

#include "widget.h"

#include <QDialog>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include "Warning_Dialog.h"

#include <QtConcurrent/QtConcurrent>

// #pragma once
// #include "MainWindow.h"

namespace Ui {
class Dialog_EnterPassWord;
}

class Dialog_EnterPassWord : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_EnterPassWord(QWidget *parent = nullptr);
    ~Dialog_EnterPassWord();
    QProcess *keyboard;
Widget *settinPage;
Warning_Dialog *warnin_dialog;

bool is_operator;

QString current_password;

void set_echoMode();
//////////////////////////////////////
Business_logic *Business_logic_layer;
 // QScopedPointer<Business_Logic> Business_logic_layer;
// MainWindow *main_window;
private slots:
    void on_Ok_btn_clicked();

    void on_Cancel_btn_clicked();
signals :
    void Widget_Show ();

private:
    Ui::Dialog_EnterPassWord *ui;
};

#endif // DIALOG_ENTERPASSWORD_H
