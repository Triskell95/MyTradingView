#pragma once

#include <QObject>
#include "qcustomplot.h"
#include "data/ohlcdata.h"

class ChartManager : public QObject {
    Q_OBJECT

public:
    explicit ChartManager(QObject *parent = nullptr);
    QCustomPlot* getPlot();
    void plotCandlesticks(const QList<OHLCData> &data);

private:
    QCustomPlot *customPlot;
    QCPFinancial *candlesticks;
};
