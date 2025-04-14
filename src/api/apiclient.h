// api/ApiClient.h
#ifndef APICLIENT_H
#define APICLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class ApiClient : public QObject {
    Q_OBJECT
public:
    ApiClient(QObject *parent = nullptr);
    void fetchOHLCData(const QUrl &url);

signals:
    void dataFetched(const QByteArray &data);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // APICLIENT_H
