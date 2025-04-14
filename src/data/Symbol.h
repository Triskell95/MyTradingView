#ifndef SYMBOL_H
#define SYMBOL_H

#include <QString>

enum typeSymbol
{
    stockFR, stockUS, currency, metal, crypto, other
};

class Symbol
{
public:
    Symbol();
    Symbol(const Symbol &other);
    Symbol(QString label, QString symbol, typeSymbol type, float price, float dailyVariation, QString currency = "USD");

    bool operator==(const Symbol &other) const;
    bool operator<(const Symbol &other) const;

    inline QString getLabel() { return _label; };
    inline QString getSymbol() { return _symbol; };
    inline float getPrice() { return _price; };
    inline float getDailyVar() { return _dailyVar; };
    inline QString getCurrency() {return _currency; };

private:
    QString _label;
    QString _symbol;
    typeSymbol _type;
    float _price;
    float _dailyVar;
    QString _currency;
};

#endif // SYMBOL_H
