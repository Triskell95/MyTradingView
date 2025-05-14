#ifndef SYMBOL_H
#define SYMBOL_H

#include <QString>
#include <QJsonObject>

enum typeSymbol
{
    stockFR, stockUS, currency, metal, crypto, other
};

class Symbol
{
public:
    Symbol();
    Symbol(const Symbol &other);
    Symbol(QString label, QString symbol, typeSymbol type = typeSymbol::other, float price = 0.0, float dailyVariation = 0.0, QString currency = "USD", QString url = QString(""));

    bool operator==(const Symbol &other) const;
    bool operator<(const Symbol &other) const;

    QJsonObject toJson() const;
    static Symbol* fromJson(const QJsonObject &obj);
    void setURL();

    inline QString getLabel()    { return _label;    };
    inline QString getSymbol()   { return _symbol;   };
    inline typeSymbol getType()  { return _type;     };
    inline float getPrice()      { return _price;    };
    inline float getDailyVar()   { return _dailyVar; };
    inline QString getCurrency() { return _currency; };
    inline QString getURL()      { return _url;      };

    void setLabel(const QString &label)        { _label = label; }
    void setSymbol(const QString &symbol)      { _symbol = symbol; }
    void setType(typeSymbol type)              { _type = type; }
    void setPrice(float price)                 { _price = price; }
    void setDailyVar(float var)                { _dailyVar = var; }
    void setCurrency(const QString &currency)  { _currency = currency; }
    void setURL(const QString &url)            { _url = url; }

private:

    QString _label;
    QString _symbol;
    typeSymbol _type;
    float _price;
    float _dailyVar;
    QString _currency;
    QString _url;
};

#endif // SYMBOL_H
