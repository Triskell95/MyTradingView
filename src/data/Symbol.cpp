#include "Symbol.h"

Symbol::Symbol():
    _label(QString("XXX")),
    _symbol(QString("XXX")),
    _type(typeSymbol::other),
    _price(0.0),
    _dailyVar(0.0),
    _currency("USD"),
    _url(QString("")),
    _nb(0),
    _buyPrice(0.0)
{

}

Symbol::Symbol(const Symbol &other):
    _label(other._label),
    _symbol(other._symbol),
    _type(other._type),
    _price(other._price),
    _dailyVar(other._dailyVar),
    _currency(other._currency),
    _url(other._url),
    _nb(other._nb),
    _buyPrice(other._buyPrice)
{

}

Symbol::Symbol(QString label, QString symbol, typeSymbol type, float price, float dailyVar, QString currency, QString url, float nb, float buy):
    _label(label),
    _symbol(symbol),
    _type(type),
    _price(price),
    _dailyVar(dailyVar),
    _currency(currency),
    _url(url),
    _nb(nb),
    _buyPrice(buy)
{

}

QJsonObject Symbol::toJson() const
{
    QJsonObject obj;
    obj["label"] = _label;
    obj["symbol"] = _symbol;
    obj["type"] = static_cast<int>(_type);
    obj["price"] = _price;
    obj["dailyVar"] = _dailyVar;
    obj["currency"] = _currency;
    obj["url"] = _url;
    obj["nb"] = _nb;
    obj["buy"] = _buyPrice;
    return obj;
}

Symbol* Symbol::fromJson(const QJsonObject &obj)
{
    QString label = obj["label"].toString();
    QString symbol = obj["symbol"].toString();
    typeSymbol type = static_cast<typeSymbol>(obj["type"].toInt());
    float price = obj["price"].toDouble();
    float dailyVar = obj["dailyVar"].toDouble();
    QString currency = obj["currency"].toString();
    QString url = obj["url"].toString();
    float nb = obj["nb"].toDouble();
    float buy = obj["buy"].toDouble();

    return new Symbol(label, symbol, type, price, dailyVar, currency, url, nb, buy);
}

QString Symbol::getStrType()
{
    QString type = "";
    switch(_type)
    {
        case stockFR:
            type = "Actions FR";
            break;
        case stockUS:
            type = "Actions US";
            break;
        case currency:
            type = "Devises";
            break;
        case metal:
            type = "Métal";
            break;
        case crypto:
            type = "Crypto";
            break;
        case other:
            type = "Autre";
            break;
    }
    return type;
}

void Symbol::setURL()
{
    // url symbol for Yahoo Finance
    if(_type == typeSymbol::stockFR)
    {
        _url = _symbol + QString(".PA");
    }
    else if(_type == typeSymbol::stockUS)
    {
        _url = _symbol;
    }
    else if(_type == typeSymbol::crypto)
    {
        _url = _symbol + QString("-") + _currency;
    }
    else if(_type == typeSymbol::metal)
    {
        _url = _symbol + _currency + QString("=X");
    }
    else if(_type == typeSymbol::currency)
    {
        _url = _symbol + _currency + QString("=X");
    }
    else
    {
        _url = _symbol;
    }
}

bool Symbol::operator==(const Symbol &other) const
{
    return (_label == other._label) && (_symbol == other._symbol) && (_type == other._type);
}

bool Symbol::operator<(const Symbol &other) const
{
    return ((_type < other._type) || (_label < other._label) || (_symbol < other._symbol));
}
