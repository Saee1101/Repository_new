#ifndef PIEVIEW_H
#define PIEVIEW_H

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
#include <QFormLayout>

class pieview : public QChart
{
    Q_OBJECT
public:
     explicit pieview(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
QPieSeries *series;
signals:

};

#endif // PIEVIEW_H
