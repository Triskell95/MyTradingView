#ifndef SYMBOLSLISTS_H
#define SYMBOLSLISTS_H

#include <QTableWidget>
#include "Symbol.h"

enum colIndex
{
    label=0, price, var, max
};

class SymbolsLists : public QObject
{
    Q_OBJECT
public:
    SymbolsLists();
    void addSymbol(Symbol* s);
    void sortList();
    void loadSymbols();
    void loadFromJsonFile();

    inline QTableWidget* getTable() { return tableWidget; };
    inline QList<Symbol*> getData() { return _list; };

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onCellClicked(int row, int column);

private:
    QTableWidget *tableWidget;
    QList<Symbol*> _list;
    QString _request;
};

#endif // SYMBOLSLISTS_H
