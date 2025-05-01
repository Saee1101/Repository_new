#include "Warning_Dialog.h"

Warning_Dialog::Warning_Dialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout=new QVBoxLayout(this);
    p=new QPushButton;
    p->setObjectName("ok_btn");

    p->setFixedSize(348,71);

    p->setText("");
    p->setStyleSheet("#ok_btn{border-image: url(:/Image/Asset 24.png);}");

    layout->addWidget(p,0,Qt::AlignCenter | Qt::AlignBottom );

    connect(p, SIGNAL(clicked()), this, SLOT(accept()));  // Close the dialog when the button is clicked

}
