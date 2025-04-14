// chart/CandlestickPlotter.h
#ifndef CANDLESTICKPLOTTER_H
#define CANDLESTICKPLOTTER_H

#include <QCustomPlot.h>
#include <QVector>

class CandlestickPlotter {
public:
    CandlestickPlotter(QCustomPlot* plotWidget);
    void plot(const QVector<double>& xData, const QVector<double>& openData,
              const QVector<double>& highData, const QVector<double>& lowData,
              const QVector<double>& closeData);

private:
    QCustomPlot* plotWidget;
};

#endif // CANDLESTICKPLOTTER_H
