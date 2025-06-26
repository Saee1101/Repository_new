#include "Dialog_ChangePassWord.h"
#include "ui_Dialog_ChangePassWord.h"

#include <QTimer>
#include <QSqlError>
#include <QDebug>
#include "Repository.h"
#include "Entities.h"

Dialog_ChangePassWord::Dialog_ChangePassWord(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Dialog_ChangePassWord),
    keyboard(new QProcess(this))
{
    ui->setupUi(this);


    QTimer::singleShot(0, ui->lineEdit_NewPassword, SLOT(setFocus()));


    keyboard->start("FreeVK.exe");
}

Dialog_ChangePassWord::~Dialog_ChangePassWord()
{
    delete ui;
    keyboard->close();
}

void Dialog_ChangePassWord::on_Set_btn_clicked()
{

    // Helper function to show warning dialog
    auto showWarningDialog = [this](const QString& objectName, const QString& imagePath, QWidget* focusWidget) {
        QPointer<Warning_Dialog> warnin_dialog = new Warning_Dialog;
        warnin_dialog->setObjectName(objectName);
        warnin_dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        warnin_dialog->setGeometry(90, 370, 1030, 247);
        warnin_dialog->setStyleSheet(QString("#%1 { background-color: rgba(255, 0, 0, 100); border-image: url(%2); }"
                                             ).arg(objectName, imagePath));
        warnin_dialog->show();

        if (focusWidget) {
            focusWidget->setFocus();
        }

        // Optionally, close the warning dialog after 5 seconds
        QTimer::singleShot(5000, warnin_dialog.data(), &Warning_Dialog::close);
    };

    // Check if new password is empty
    if (ui->lineEdit_NewPassword->text().isEmpty() || ui->lineEdit_NewPassword->text().trimmed().isEmpty()) {
        showWarningDialog("warning_dialog_Newpassword", ":/Image/Asset 11.png", ui->lineEdit_NewPassword);
        return;
    }

    // Check if confirm password is empty or mismatched
    if (ui->lineEdit_ConfirmNewPassword->text().isEmpty() || ui->lineEdit_ConfirmNewPassword->text() != ui->lineEdit_NewPassword->text()) {
        qDebug() << "Check if confirm password is empty or mismatched";
        showWarningDialog("warning_dialog_ConfirmNewpassword", ":/Image/Asset 15.png", ui->lineEdit_ConfirmNewPassword);
        return;
    }
QScopedPointer<Business_logic> Business_logic_layer(new Business_logic);
    try {

        QVariantMap data;
        data["password"] = ui->lineEdit_NewPassword->text();


        QString condition = "user_name = 'admin'";

        if (!Business_logic_layer->entities.CRUD_user_db.update(condition, data)) {
            qDebug() << "Failed to update password for admin!";
        } else {
            qDebug() << "Password updated successfully for admin!";
        }

        keyboard->close();
        close();

    } catch (const std::exception& e) {
        qDebug() << "Exception caught:" << e.what();
    }
}

void Dialog_ChangePassWord::on_Cancel_btn_clicked()
{
    keyboard->close();
    accept();
}
