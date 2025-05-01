#ifndef DIALOG_CHANGEPASSWORD_H
#define DIALOG_CHANGEPASSWORD_H

#include <Business_logic.h>
#include <QDialog>
#include <qmessagebox.h>
#include <qprocess.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include "Warning_Dialog.h"
#include "qdebug.h"
#include <QScopedPointer>
namespace Ui {
class Dialog_ChangePassWord;
}

class Dialog_ChangePassWord : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ChangePassWord(QWidget *parent = nullptr);
    ~Dialog_ChangePassWord();
 QProcess *keyboard;
 Warning_Dialog *warnin_dialog;
  // Business_logic *Business_logic_layer;
  QScopedPointer<Business_logic> Business_logic_layer;
private slots:
    void on_Set_btn_clicked();

    void on_Cancel_btn_clicked();

private:
    Ui::Dialog_ChangePassWord *ui;
};

#endif // DIALOG_CHANGEPASSWORD_H
