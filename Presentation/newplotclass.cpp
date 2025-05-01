#include "newplotclass.h"

newplotclass::newplotclass(QWidget *parent) : QWidget(parent)
{
customPlot=new QCustomPlot(this);
//////////////////////////////////  Axis SetTicks  //////////////////////
QPen pen_white ;
pen_white.setColor(QColor(255,255,255));
customPlot->xAxis->setTickLabelColor(QColor(255,255,255));
customPlot->xAxis->setBasePen(pen_white);
customPlot->xAxis->setLabelColor(QColor(255,255,255));
customPlot->xAxis->setTickPen(pen_white);
customPlot->xAxis->setSubTickPen(pen_white);
customPlot->yAxis->setTickLabelColor(QColor(255,255,255));
customPlot->yAxis->setBasePen(pen_white);
customPlot->yAxis->setLabelColor(QColor(255,255,255));
customPlot->yAxis->setTickPen(pen_white);
customPlot->yAxis->setSubTickPen(pen_white);
customPlot->xAxis->setSelectedTickLabelColor(QColor(255,255,255));
customPlot->xAxis->setTickPen(pen_white);
customPlot->yAxis->setTickPen(pen_white);
//////////////////////////////////  Red & Green  Chart //////////////////////
postcounter=0;
QPen Red_pen, Green_pen;
Red_pen.setColor(QColor(100,0,0));
Green_pen.setColor(QColor(0,100,0));
Red_pen.setWidth(5);
Green_pen.setWidth(5);
customPlot->addGraph();
customPlot->addGraph();
customPlot->graph(0)->setPen(Red_pen);
customPlot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,5));
customPlot->graph(1)->setPen(Green_pen);
customPlot->graph(1)->setLineStyle(QCPGraph::lsImpulse);
customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,5));

customPlot->setBackground(QBrush(QColor(0,0,0)));

////////////////////////////// Make Empity textLable /////////////

for (int k=0;k<20;k++) {

    textLable[k]=new QCPItemText(customPlot);
    textLable[k]->position->setCoords(k,0);
    textLable[k]->setText(" ");
    textLable[k]->setRotation(90);
    textLable[k]->setFont(QFont(font().family(),12));
    textLable[k]->setColor(QColor(255,255,255));
}
customPlot->replot();

}

void newplotclass::setparameter(double WindowsWidth, double WindowsHight, double Xrang, double Yrange,
                                double main_value,double up_telorance,double low_telorance)
{
    customPlot->update();
Nominal = main_value;
Up_tel = up_telorance;
Lo_tel = low_telorance;
    ///////////////////////////// Set Title //////////////////
//    customPlot->plotLayout()->insertRow(0);
//     QCPTextElement *title = new QCPTextElement(customPlot, Title, QFont("sans", 10, QFont::Bold));
//     title->setTextColor(QColor(255,255,0));
//     customPlot->plotLayout()->addElement(0, 0, title);
    //////////////////////////////////////////////////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    customPlot->yAxis->setTicker(textTicker);
    textTicker->addTick(0, QString::number(main_value));
    textTicker->addTick(up_telorance-main_value, QString::number(up_telorance));
    textTicker->addTick(low_telorance-main_value, QString::number(low_telorance));
    ///////////////////////////////////// Chart Background /////////////////
 //
    ////////////////////////////////////////////////////////////////////////

    customPlot->setFixedSize(WindowsWidth,WindowsHight);
    customPlot->xAxis->setRange(0,Xrang);
    customPlot->yAxis->setRange(-Yrange,Yrange);

    QCPItemLine *Up_parallelLine=new QCPItemLine(customPlot);
    Up_parallelLine->start->setCoords(0,up_telorance-main_value);
   Up_parallelLine->end->setCoords(21,up_telorance-main_value);
    QCPItemLine *Down_parallelLine=new QCPItemLine(customPlot);
    Down_parallelLine->start->setCoords(0,low_telorance-main_value);
    Down_parallelLine->end->setCoords(21,low_telorance-main_value);

    QVector<qreal> dashPattern;
    dashPattern << 3 << 5;
    QPen pen_Yellow;
    pen_Yellow.setColor(Qt::yellow);
    pen_Yellow.setStyle(Qt::CustomDashLine);
    pen_Yellow.setStyle(Qt::DotLine);  // Set the line style to dotted
    pen_Yellow.setWidth(3);            // Set line width
    pen_Yellow.setDashPattern(dashPattern);
    Up_parallelLine->setPen(pen_Yellow);
    pen_Yellow.setDashPattern(dashPattern);
    Down_parallelLine->setPen(pen_Yellow);
    customPlot->xAxis->setRange(0,21);
    customPlot->yAxis->setRange((Lo_tel-Nominal)*1.2,(Up_tel-Nominal)*1.2);
    customPlot->replot();

}

void newplotclass::setData(double data)
{
    // qDebug()<<"newplot data :"<<data<<endl;
    if(data>Up_tel || data<Lo_tel){
        status=false;
        vec_x_r.push_back(1);
        vec_y_r.append(data-Nominal);

    }else{
        status=true;
        vec_x.push_back(1);
        vec_y.append(data-Nominal);
    }

customPlot->graph(1)->setData(vec_x,vec_y);
customPlot->graph(0)->setData(vec_x_r,vec_y_r);
QString s;
postcounter++;
textLable[0]->position->setCoords(1,-copysign(1,data-Nominal)*(Up_tel-Nominal)*0.19);
//textLable[0]->setText(s.setNum(postcounter));
textLable[0]->setText(s.number(data, 'f', 2));
//textLable[0]->setFont(QFont(font().family(),20));
if(postcounter==20)
    postcounter=0;
for (int k=0;k<vec_x_r.length();k++)
{
    vec_x_r[k]++;

}
for (int k=0;k<vec_x.length();k++)
    vec_x[k]++;
if(!vec_x.isEmpty())
    if(vec_x.first()>20){
        vec_x.pop_front();
        vec_y.pop_front();
    }
if(!vec_x_r.isEmpty())
    if(vec_x_r.first()>20){
        vec_x_r.pop_front();
        vec_y_r.pop_front();
    }



customPlot->replot();
for (int k=19;k>0;k--) {
  //   textLable[k]->setFont(QFont(font().family(),20));
    textLable[k]->setText(textLable[k-1]->text());
    textLable[k]->position->setCoords(k+1,textLable[k-1]->position->coords().y());
    //      textLable[k]->position->setCoords(k+1,textLable[k-1]->text().toDouble());
}


}

bool newplotclass::statusData()
{
  //  qDebug()<<"newplot :"<<status<<endl;
    return status;
}



