// data/OHLCData.cpp
#include "OHLCData.h"
#include <QJsonValue>

void OHLCData::fromJsonArray(const QJsonArray &data) {
    for (const auto& item : data) {
        QJsonArray ohlc = item.toArray();
        qint64 timestamp = ohlc[0].toVariant().toLongLong() / 1000;
        double open = ohlc[1].toDouble();
        double high = ohlc[2].toDouble();
        double low = ohlc[3].toDouble();
        double close = ohlc[4].toDouble();

        xData.append(timestamp);
        openData.append(open);
        highData.append(high);
        lowData.append(low);
        closeData.append(close);
    }
}

void OHLCData::processData(QVector<OHLCData>& ohlcData)
{
    // Exemple de traitement simple des données : affichage des données OHLC
    qDebug() << "Traitement des données OHLC :";

    for (const OHLCData& ohlc : ohlcData) {
        qDebug() << "Open:" << ohlc.openData << " High:" << ohlc.highData << " Low:" << ohlc.lowData << " Close:" << ohlc.closeData;
    }

    // Vous pouvez ajouter des opérations sur les données ici (calculs, transformations, etc.)
}
