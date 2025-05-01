#include "barview.h"

barview::barview(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
 set0 = new QBarSet("D4");
 set1 = new QBarSet("D5");

 m_series=new QBarSeries();

 m_series->append(set0);
 m_series->append(set1);

 set0->insert(0,0);
 set1->insert(0,0);

 addSeries(m_series);
 QValueAxis *axisY = new QValueAxis();
 axisY->setRange(0,100);
 addAxis(axisY, Qt::AlignLeft);
 m_series->attachAxis(axisY);
 legend()->setColor(QColor(255,255,255));
// legend()->setAlignment(Qt::AlignCenter);
 legend()->setFont(QFont("Arial", 10));
 axisY->setLabelsBrush(QBrush(QColor(255,255,255)));
 setBackgroundBrush(QBrush(QColor(44,44,44)));
 legend()->setLabelBrush(QBrush(QColor(255,255,255)));
//    series = new QPieSeries();
//    series->append("accept",0);
//    series->append("reject",0);
////![1]

////![2]
////!
//    setBackgroundBrush(QBrush(QColor(44,44,44)));
//    series->slices().at(0)->setBrush(Qt::green);
//    series->slices().at(1)->setBrush(Qt::red);
//    addSeries(series);
//    //legend()->hide();
//    legend()->setLabelBrush(QBrush(QColor(255,255,255)));
//    series->slices().at(0)->setLabelBrush(QBrush(QColor(255,255,255)));
//    series->slices().at(1)->setLabelBrush(QBrush(QColor(255,255,255)));
}
