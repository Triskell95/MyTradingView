// api/ApiClient.cpp
#include "ApiClient.h"

ApiClient::ApiClient(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this)) {
    connect(manager, &QNetworkAccessManager::finished, this, &ApiClient::onReplyFinished);
}

void ApiClient::fetchOHLCData(const QUrl &url) {
    manager->get(QNetworkRequest(url));
}

void ApiClient::onReplyFinished(QNetworkReply *reply) {
    QByteArray data = reply->readAll();
    emit dataFetched(data);
    reply->deleteLater();
}
