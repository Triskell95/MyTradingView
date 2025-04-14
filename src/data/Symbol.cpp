#include "Symbol.h"

Symbol::Symbol():
    _label(QString("XXX")),
    _symbol(QString("XXX")),
    _type(typeSymbol::other),
    _price(0.0),
    _dailyVar(0.0)
{

}

Symbol::Symbol(const Symbol &other):
    _label(other._label),
    _symbol(other._symbol),
    _type(other._type),
    _price(other._price),
    _dailyVar(other._dailyVar),
    _currency(other._currency)
{

}

Symbol::Symbol(QString label, QString symbol, typeSymbol type, float price, float dailyVar, QString currency):
    _label(label),
    _symbol(symbol),
    _type(type),
    _price(price),
    _dailyVar(dailyVar),
    _currency(currency)
{

}

bool Symbol::operator==(const Symbol &other) const
{
    return (_label == other._label) && (_symbol == other._symbol) && (_type == other._type);
}

bool Symbol::operator<(const Symbol &other) const
{
    return ((_type < other._type) && (_symbol < other._symbol));
}
