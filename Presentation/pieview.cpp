#include "pieview.h"


pieview::pieview(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags)

{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    series = new QPieSeries();

    series->append("accept",0);
    series->append("reject",0);
    series->setPieSize(0.9);

    series->setVerticalPosition(0.3);

//![1]

//![2]
//!


    setBackgroundBrush(QBrush(QColor(44,44,44,0)));


//setBackgroundBrush(QBrush(QColor(10,10,10)));

    series->slices().at(0)->setBrush(Qt::green );

    series->slices().at(1)->setBrush(Qt::red);
    addSeries(series);
    legend()->hide();

//    legend()->setLabelBrush(QBrush(QColor(255,255,255)));

//   legend()->setAlignment(Qt::AlignBottom );
//legend()->setLayoutDirection(Qt::RightToLeft);

//   legend()->setTransformOriginPoint(1,1);
//   >legend()->setGeometry(QRectF(m_legendPosX->value(),
//                                             m_legendPosY->value(),
//                                             m_legendWidth->value(),
//                                             m_legendHeight->value()));

     //          setLabelFont(QFont("Arial", 8));
//     legend()->setFont(QFont("Arial", 10));

//legend()->setContentsMargins(1,1,1,100);

//     legend()->setLabelBrush(QBrush(QColor("transparent")));
    series->slices().at(0)->setLabelBrush(QBrush(QColor(255,255,255)));
    series->slices().at(1)->setLabelBrush(QBrush(QColor(255,255,255)));
}
