#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include "data/ohlcdata.h"

class ApiClient : public QObject {
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr);
    void fetchOHLC(const QString &coinId, std::function<void(QList<OHLCData>)> callback);

private:
    QNetworkAccessManager *manager;
};
