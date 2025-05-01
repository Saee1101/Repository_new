#ifndef BARVIEW_H
#define BARVIEW_H
#include <QObject>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QTimer>
#include<QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QObject>
// QT_CHARTS_USE_NAMESPACE

class barview : public QChart
{
    Q_OBJECT
public:
    explicit barview(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    //QBarSeries *series;
    QBarSet*   set0;
    QBarSet*   set1;
    QBarSet*   set2;
    QBarSet*   set3;
    QBarSet*   set4;
    QBarSet*   set5;
    QBarSeries*   m_series;
signals:

};

#endif // BARVIEW_H
