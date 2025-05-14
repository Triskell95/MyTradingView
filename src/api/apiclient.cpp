#include "apiclient.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ApiClient::ApiClient(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this)) {}

void ApiClient::fetchOHLC(const QString &coinId, std::function<void(QList<OHLCData>)> callback) {

    QString url = QString("https://api.coingecko.com/api/v3/coins/%1/ohlc?vs_currency=usd&days=365").arg(coinId);
    qInfo() << "Url request :  " << url;

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

void ApiClient::fetchYahooQuotes(const QList<Symbol*>& symbols, std::function<void(QList<Symbol*>)> callback)
{
    QString url = buildYahooRequestUrl(symbols); // Construire l'URL pour l'API de Yahoo Finance
    qInfo() << "Url request :  " << url;

    QNetworkRequest request{QUrl(url)};
    request.setUrl(QUrl("yahoo-finance-real-time1.p.rapidapi.com/stock/v2/get-summary?symbol=GOOG"));
    request.setRawHeader("X-RapidAPI-Key", "92a2490f3dmsh5efdb9906c6831ap155e58jsn99a704e7300f");
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply, callback]() {
        QList<Symbol*> symbols;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isObject()) {
            QJsonObject jsonObject = doc.object();
            QJsonArray jsonArray = jsonObject["quoteResponse"].toObject()["result"].toArray();
            for (const QJsonValue &value : jsonArray) {
                QJsonObject symbolObject = value.toObject();
                Symbol* symbol = parseSymbol(symbolObject);  // Créer le Symbol sans toucher à la structure
                if (symbol) {
                    symbols.append(symbol);
                }
            }
        }
        callback(symbols);  // Passer les symboles traités à la fonction de rappel
        reply->deleteLater();
    });
}

void ApiClient::fetchFinnhubQuote(const QString &symbol, const QString &apiKey, std::function<void(QJsonObject)> callback) {
    QString url = QString("https://finnhub.io/api/v1/quote?symbol=%1&token=%2").arg(symbol, apiKey);
    QNetworkRequest request((QUrl(url)));

    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply, callback]() {
        QJsonObject result;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isObject()) {
            result = doc.object();
        }
        callback(result);
        reply->deleteLater();
    });
}

QString ApiClient::buildYahooRequestUrl(const QList<Symbol*>& symbols)
{
    QString url = "https://query1.finance.yahoo.com/v7/finance/quote?symbols=";
    bool isFirst = true;

    for (auto s : symbols) {
        if (!s->getURL().isEmpty()) {
            if (!isFirst) {
                url += ",";
            } else {
                isFirst = false;
            }
            url += s->getURL();
        }
    }
    return url;
}

Symbol* ApiClient::parseSymbol(const QJsonObject &symbolObject)
{
    // Créer un objet Symbol en utilisant le constructeur existant, sans changer sa structure
    QString symbol = symbolObject["symbol"].toString();
    QString label = symbolObject["longName"].toString();
    float price = symbolObject["regularMarketPrice"].toDouble();
    float dailyVariation = symbolObject["regularMarketChange"].toDouble();
    QString currency = symbolObject["currency"].toString();
    QString url = symbolObject["url"].toString(); // Si le champ URL existe dans les données JSON

    // On suppose ici que le type du symbole est `stockUS` par défaut, mais cela peut être ajusté
    return new Symbol(label, symbol, typeSymbol::stockUS, price, dailyVariation, currency, url);
}

void ApiClient::saveToJsonFile(QList<Symbol*> symbols, const QString &filename)
{
    QJsonObject root;
    for (Symbol* symbol : symbols) {
        root[symbol->getSymbol()] = symbol->toJson();  // Utiliser la méthode toJson de Symbol
    }
    QJsonDocument doc(root);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

QList<Symbol*> ApiClient::loadSymbolsFromJson(const QString &filename)
{
    QList<Symbol*> symbols;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();
        for (const QString &key : root.keys()) {
            QJsonObject symbolObject = root[key].toObject();
            Symbol* symbol = Symbol::fromJson(symbolObject);  // Utiliser la méthode `fromJson` de Symbol
            symbols.append(symbol);
        }
    }
    return symbols;
}
