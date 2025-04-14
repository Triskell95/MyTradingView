#include "apiclient.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ApiClient::ApiClient(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this)) {}

void ApiClient::fetchOHLC(const QString &coinId, std::function<void(QList<OHLCData>)> callback) {
    QString url = QString("https://api.coingecko.com/api/v3/coins/%1/ohlc?vs_currency=usd&days=365").arg(coinId);
    QNetworkRequest request((QUrl(url)));

    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply, callback]() {
        QList<OHLCData> data;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isArray()) {
            for (auto val : doc.array()) {
                QJsonArray entry = val.toArray();
                if (entry.size() >= 5) {
                    qint64 timestamp = static_cast<qint64>(entry[0].toDouble());
                    double open = entry[1].toDouble();
                    double high = entry[2].toDouble();
                    double low = entry[3].toDouble();
                    double close = entry[4].toDouble();
                    data.append(OHLCData{timestamp / 1000, open, high, low, close});
                }
            }
        }
        callback(data);
        reply->deleteLater();
    });
}
