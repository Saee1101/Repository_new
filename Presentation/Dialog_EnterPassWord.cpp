#include "Dialog_EnterPassWord.h"
#include "ui_Dialog_EnterPassWord.h"

#include <QTimer>
#include <qmessagebox.h>




Dialog_EnterPassWord::Dialog_EnterPassWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_EnterPassWord)
{

    ui->setupUi(this);
    QTimer::singleShot(0,ui->lineEdit_Enterpassword,SLOT(setFocus()));
    keyboard = new QProcess(this);
    keyboard->start("FreeVK.exe");

    is_operator = true;
    //ui->lineEdit_Enterpassword->setFocus();
    //ui->lineEdit_Enterpassword->setText("hello");
    //QTimer::singleShot(0,ui->lineEdit_Enterpassword,SLOT(setFocus()));

}

Dialog_EnterPassWord::~Dialog_EnterPassWord()
{

    delete ui;
}

void Dialog_EnterPassWord::set_echoMode()
{
    ui->lineEdit_Enterpassword->setEchoMode(QLineEdit::Password);
}

void Dialog_EnterPassWord::on_Ok_btn_clicked()
{

    qDebug()<<"current_password  " <<current_password;
    if (ui->lineEdit_Enterpassword->text()=="" || ui->lineEdit_Enterpassword->text() != current_password)
    {

        warnin_dialog=new Warning_Dialog;
        warnin_dialog->setObjectName("warning_dialog_Enterpassword");
        warnin_dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        warnin_dialog->setGeometry(90,370,1030,247);
        warnin_dialog->setStyleSheet("#warning_dialog_Enterpassword{	background-color: rgba(0, 0, 0,0); border-image: url(:/Image/Asset 9.png);}");
        warnin_dialog->show();
        ui->lineEdit_Enterpassword->setFocus();
    }

    else if(ui->lineEdit_Enterpassword->text()==current_password)
    {

        ui->lineEdit_Enterpassword->setText("");
        emit Widget_Show();
        keyboard->close();
        accept();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("password is incorrect");
        msgBox.exec();
        ui->lineEdit_Enterpassword->setFocus();

    }

    ui->lineEdit_Enterpassword->clear();
    keyboard->close();
}


void Dialog_EnterPassWord::on_Cancel_btn_clicked()
{
    ui->lineEdit_Enterpassword->setText("");
    keyboard->close();
    accept();
}
