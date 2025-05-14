#include "FileManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

FileManager::FileManager()
{
    configPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(configPath);

    loadConfig(); // initialise listSymbolsPath
}

void FileManager::loadConfig()
{
    QSettings settings(configPath + "/config.ini", QSettings::IniFormat);
    listSymbolsPath = settings.value("Files/dataPath", configPath + "/data").toString();
    QDir().mkpath(listSymbolsPath);
}

QString FileManager::loadFinnhubKey()
{
    QSettings settings(configPath + "/config.ini", QSettings::IniFormat);
    QString path = settings.value("Files/dataPath", configPath + "/data").toString();

    QFile file(path + "/finnhub.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Impossible d'ouvrir le fichier:" << path;
        return QString();
    }

    QTextStream in(&file);
    QString firstLine = in.readLine(); // Lit la première ligne
    file.close();

    return firstLine;
}

void FileManager::saveConfig()
{
    QSettings settings(configPath + "/config.ini", QSettings::IniFormat);
    settings.setValue("Files/dataPath", listSymbolsPath);
}

QString FileManager::getDataPath() const
{
    return listSymbolsPath;
}

void FileManager::setDataPath(const QString& path)
{
    listSymbolsPath = path;
    saveConfig();
}

bool FileManager::saveSymbols(const QList<Symbol*>& symbols, QString filename)
{
    QJsonArray array;
    for (const auto& sym : symbols)
    {
        QJsonObject obj;
        obj["label"]    = sym->getLabel();
        obj["symbol"]   = sym->getSymbol();
        obj["type"]     = sym->getType();
        obj["price"]    = (QString("%1").arg(sym->getPrice(), 0, 'f', 4));
        obj["var"]      = (QString("%1").arg(sym->getDailyVar(), 0, 'f', 4));
        obj["currency"] = sym->getCurrency();
        obj["url"]      = sym->getURL();
        obj["nb"]       = (QString("%1").arg(sym->getNb()));
        obj["buy"]      = (QString("%1").arg(sym->getBuyPrice(), 0, 'f', 4));
        array.append(obj);
    }

    QFile file(listSymbolsPath + "/" + filename + ".json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson());
        file.close();
        return true;
    }
    return false;
}

QList<Symbol*> FileManager::loadSymbols(QString filename)
{
    QList<Symbol*> symbols;

    QFile file(listSymbolsPath + "/" + filename + ".json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
        for (const QJsonValue& val : array) {
            QJsonObject obj = val.toObject();
            Symbol* sym = new Symbol(
                QString(obj["label"].toString()),
                QString(obj["symbol"].toString()),
                typeSymbol(obj["type"].toInt()),
                QString(obj["price"].toString()).toFloat(),
                QString(obj["var"].toString()).toFloat(),
                QString(obj["currency"].toString()),
                QString(obj["url"].toString()),
                QString(obj["nb"].toString()).toInt(),
                QString(obj["buy"].toString()).toFloat()
                );
            symbols.append(sym);
        }
        file.close();
    }

    return symbols;
}
