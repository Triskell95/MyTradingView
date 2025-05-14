#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include "Symbol.h"

class FileManager
{
public:
    FileManager();

    QString getDataPath() const;
    void setDataPath(const QString& path);

    QString loadFinnhubKey();
    void saveFinnhubKey(QString key);

    bool saveSymbols(const QList<Symbol*>& symbols, QString filename);
    QList<Symbol*> loadSymbols(QString filename);

private:
    QString configPath;
    QString listSymbolsPath;

    void loadConfig();
    void saveConfig();
};

#endif // FILEMANAGER_H
