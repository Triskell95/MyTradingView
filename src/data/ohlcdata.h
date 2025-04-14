// data/OHLCData.h
#ifndef OHLC_DATA_H
#define OHLC_DATA_H

#include <QVector>
#include <QJsonArray>

class OHLCData {
public:
    QVector<double> xData;
    QVector<double> openData;
    QVector<double> highData;
    QVector<double> lowData;
    QVector<double> closeData;

    void fromJsonArray(const QJsonArray &data);
    void processData(QVector<OHLCData>& ohlcData);

private:

};

#endif // OHLC_DATA_H
