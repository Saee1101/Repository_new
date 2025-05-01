#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>

class Dialog_ : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog_(QWidget *parent = nullptr);
QPushButton *pushbutton;
signals:

};

#endif // DIALOG_H
