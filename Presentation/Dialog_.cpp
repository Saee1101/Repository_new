#include "Dialog_.h"

Dialog_::Dialog_(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout_=new QVBoxLayout(this);
    pushbutton=new QPushButton;
    pushbutton->setObjectName("ok_btn");
pushbutton->setFixedSize(348,71);
//p->setGeometry(20,100,300,50);
    pushbutton->setText("");
    pushbutton->setStyleSheet("#ok_btn{border-image: url(:/Image/Asset 19.png);}");

    layout_->addWidget(pushbutton,0,Qt::AlignCenter | Qt::AlignBottom );

    connect(pushbutton, SIGNAL(clicked()), this, SLOT(accept()));
}
