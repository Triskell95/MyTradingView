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
    Symbol(QString label, QString symbol, typeSymbol type, float price, float dailyVar, QString currency, QString url, int nb, float buy);

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
    inline int getNb()           { return _nb;       };
    inline float getBuyPrice()   { return _buyPrice; };


    void setLabel(const QString &label)        { _label = label; }
    void setSymbol(const QString &symbol)      { _symbol = symbol; }
    void setType(const typeSymbol &type)       { _type = type; }
    void setPrice(const float &price)          { _price = price; }
    void setDailyVar(const float &var)         { _dailyVar = var; }
    void setCurrency(const QString &currency)  { _currency = currency; }
    void setURL(const QString &url)            { _url = url; }
    void setNb(const int &nb)                  { _nb = nb; }
    void setBuyPrice(const float &buy)         { _buyPrice = buy;}

private:

    QString _label;
    QString _symbol;
    typeSymbol _type;
    float   _price;
    float   _dailyVar;
    QString _currency;
    QString _url;
    int     _nb;
    float   _buyPrice;
};

#endif // SYMBOL_H
