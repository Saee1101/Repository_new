#ifndef WARNING_DIALOG_H
#define WARNING_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>

class Warning_Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Warning_Dialog(QWidget *parent = nullptr);
QPushButton *p;
signals:

};

#endif // WARNING_DIALOG_H
