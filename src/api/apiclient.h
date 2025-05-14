#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QList>
#include "data/ohlcdata.h"
#include <functional>
#include "data/Symbol.h"  // Assurez-vous d'inclure la classe Symbol

class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr);

    void fetchOHLC(const QString &coinId, std::function<void(QList<OHLCData>)> callback);

    // Récupérer les cotations pour une liste de symboles et appeler un callback avec les résultats
    void fetchYahooQuotes(const QList<Symbol*>& symbols, std::function<void(QList<Symbol*>)> callback);

    void fetchFinnhubQuote(const QString &symbol, const QString &apiKey, std::function<void(QJsonObject)> callback);

    // Sauvegarder la liste des symboles dans un fichier JSON
    void saveToJsonFile(QList<Symbol*> symbols, const QString &filename);

    // Charger les symboles depuis un fichier JSON
    QList<Symbol*> loadSymbolsFromJson(const QString &filename);


private:
    QNetworkAccessManager* manager;  // Gestionnaire de requêtes réseau

    // Construire l'URL de la requête pour l'API Yahoo Finance
    QString buildYahooRequestUrl(const QList<Symbol*>& symbols);

    // Parser les données JSON d'un symbole pour créer un objet Symbol
    Symbol* parseSymbol(const QJsonObject &symbolObject);
};

#endif // APICLIENT_H
