#pragma once

#include <QObject>
#include "data/ohlcdata.h"

#include <QtCharts/QChartView>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>
#include <QTime>
#include "CustomChartView.h"

class ChartManager : public QObject {
    Q_OBJECT

public:
    explicit ChartManager(QObject *parent = nullptr);

    void setChartData(const QList<OHLCData> &ohlcList);
    void setChartView();

    inline QChartView* getChartView() { return _chartView; };

private:

    QCandlestickSeries* _series;
    QChart* _chart;
    CustomChartView* _chartView;
    void setStyle();

    qreal _minPrice;
    qreal _maxPrice;
    qint64 _minTime;
    qint64 _maxTime;

    QDateTimeAxis* _axisX;
    QValueAxis* _axisY;
};
