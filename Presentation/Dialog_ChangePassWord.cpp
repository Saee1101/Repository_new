#include "Dialog_ChangePassWord.h"
#include "ui_Dialog_ChangePassWord.h"

#include <QTimer>
#include <QSqlError>
#include <QDebug>
#include "Repository.h" // اضافه کردن هدر مخزن
#include "Entities.h"         // اضافه کردن هدر موجودیت‌ها

Dialog_ChangePassWord::Dialog_ChangePassWord(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Dialog_ChangePassWord),
    keyboard(new QProcess(this)) // مقداردهی کیبورد
{
    ui->setupUi(this);

    // فوکوس بر روی فیلد رمز عبور جدید
    QTimer::singleShot(0, ui->lineEdit_NewPassword, SLOT(setFocus()));

    // راه‌اندازی کیبورد مجازی
    keyboard->start("FreeVK.exe");
}

Dialog_ChangePassWord::~Dialog_ChangePassWord()
{
    delete ui;
    keyboard->close(); // بستن کیبورد هنگام تخریب
}

void Dialog_ChangePassWord::on_Set_btn_clicked()
{
    // Helper function to show warning dialog
    auto showWarningDialog = [this](const QString& objectName, const QString& imagePath, QWidget* focusWidget) {
        QScopedPointer<Warning_Dialog> warnin_dialog(new Warning_Dialog);
        warnin_dialog->setObjectName(objectName);
        warnin_dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        warnin_dialog->setGeometry(90, 370, 1030, 247);
        warnin_dialog->setStyleSheet(QString("#%1 { background-color: rgba(0, 0, 0, 0); border-image: url(%2); }").arg(objectName, imagePath));
        warnin_dialog->show();

        if (focusWidget) {
            focusWidget->setFocus();
        }

        // Optionally, close the warning dialog after 3 seconds
        QTimer::singleShot(3000, warnin_dialog.data(), &Warning_Dialog::close);
    };

    // Check if new password is empty
    if (ui->lineEdit_NewPassword->text().isEmpty() || ui->lineEdit_NewPassword->text().trimmed().isEmpty()) {
        showWarningDialog("warning_dialog_Newpassword", ":/Image/Asset 11.png", ui->lineEdit_NewPassword);
        return;
    }

    // Check if confirm password is empty or mismatched
    if (ui->lineEdit_ConfirmNewPassword->text().isEmpty() || ui->lineEdit_ConfirmNewPassword->text() != ui->lineEdit_NewPassword->text()) {
        showWarningDialog("warning_dialog_ConfirmNewpassword", ":/Image/Asset 15.png", ui->lineEdit_ConfirmNewPassword);
        return;
    }

    try {
        // دسترسی به موجودیت‌ها و مخزن
        Entities entities(QSqlDatabase::database());

        // استخراج شناسه کاربر با استفاده از نام کاربری
        // User user = entities.CRUD_user_db.readByUsername("admin");
        // if (user.userName.isEmpty()) {
        //     qDebug() << "User not found!";
        //     showWarningDialog("warning_dialog_UserNotFound", ":/Image/Asset_UserNotFound.png", nullptr);
        //     return;
        // }

        QVariantMap data;
        data["password"] = ui->lineEdit_NewPassword->text();  // مقدار جدید برای ستون "password"

        // شرط به‌روزرسانی: نام کاربری برابر با "admin"
        QString condition = "username = 'admin'";


        // فراخوانی متد update
        if (!Business_logic_layer->entities.CRUD_user_db.update(condition, data)) {
            qDebug() << "Failed to update password for admin!";
        } else {
            qDebug() << "Password updated successfully for admin!";
        }

        // بستن کیبورد و دیالوگ تغییر رمز عبور
        keyboard->close();
        close();

    } catch (const std::exception& e) {
        qDebug() << "Exception caught:" << e.what();
    }
}
// #include "Dialog_ChangePassWord.h"
// #include "ui_Dialog_ChangePassWord.h"

// #include <QTimer>



// Dialog_ChangePassWord::Dialog_ChangePassWord(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::Dialog_ChangePassWord)


// {
//     ui->setupUi(this);
//     QTimer::singleShot(0,ui->lineEdit_NewPassword,SLOT(setFocus()));
//     keyboard = new QProcess(this);
//      keyboard->start("FreeVK.exe");
//     // Business_logic_layer = new Business_logic();
// }

// Dialog_ChangePassWord::~Dialog_ChangePassWord()
// {
//     delete ui;
// }
// void Dialog_ChangePassWord::on_Set_btn_clicked() {
//     // Helper function to show warning dialog
//     QScopedPointer<Business_logic> Business_logic_layer(new Business_logic);
//     auto showWarningDialog = [this](const QString& objectName, const QString& imagePath, QWidget* focusWidget) {
//         QScopedPointer<Warning_Dialog> warnin_dialog(new Warning_Dialog);
//         warnin_dialog->setObjectName(objectName);
//         warnin_dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
//         warnin_dialog->setGeometry(90, 370, 1030, 247);
//         warnin_dialog->setStyleSheet(QString("#%1 { background-color: rgba(0, 0, 0, 0); border-image: url(%2); }").arg(objectName, imagePath));
//         warnin_dialog->show();

//         if (focusWidget) {
//             focusWidget->setFocus();
//         }

//         // Optionally, close the warning dialog after 3 seconds
//         QTimer::singleShot(3000, warnin_dialog.data(), &Warning_Dialog::close);
//     };

//     // Check if new password is empty
//     if (ui->lineEdit_NewPassword->text().isEmpty() || ui->lineEdit_NewPassword->text() == " ") {
//         showWarningDialog("warning_dialog_Newpassword", ":/Image/Asset 11.png", ui->lineEdit_NewPassword);
//     }
//     // Check if confirm password is empty or mismatched
//     else if (ui->lineEdit_ConfirmNewPassword->text().isEmpty() || ui->lineEdit_ConfirmNewPassword->text() != ui->lineEdit_NewPassword->text()) {
//         showWarningDialog("warning_dialog_ConfirmNewpassword", ":/Image/Asset 15.png", ui->lineEdit_ConfirmNewPassword);
//     }
//     // If everything is valid, update the password
//     else {
//         try {

//             // Business_logic_layer->entities.CRUD_user_db.Update("admin", ui->lineEdit_NewPassword->text());
//             QVariantMap data;
//             data["password"] = ui->lineEdit_NewPassword->text();
//             Business_logic_layer->entities.CRUD_user_db.update("admin", data);

//         } catch (const std::exception& e) {
//             qDebug() << "Exception caught:" << e.what();
//         }
//           // Business_logic_layer->entities.push_map();
//         keyboard->close();
//         close();
//     }
// }

void Dialog_ChangePassWord::on_Cancel_btn_clicked()
{
    keyboard->close();
    accept();
}
