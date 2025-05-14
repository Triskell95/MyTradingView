#ifndef SYMBOLSLISTS_H
#define SYMBOLSLISTS_H

#include <QTableWidget>
#include "Symbol.h"
#include <QStandardItemModel>

enum colPosition
{
    LABEL = 0, NB, BUY, TOTAL_INVEST, PRICE, TOTAL_VAL, VAR, REPART, TYPE, MAX
};

enum colIndex
{
    label=0, price, var, max
};

class SymbolsLists : public QObject
{
    Q_OBJECT
public:
    SymbolsLists(QString filename = "");
    void addSymbol(Symbol* s);
    void sortList();
    void loadSymbols();

    inline QTableWidget* getTable() { return tableWidget; };
    inline QList<Symbol*> getData() { return _list; };

    void fillQTableView(QTableView* table, QStandardItemModel* model);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onCellClicked(int row, int column);

private:
    QTableWidget *tableWidget;
    QList<Symbol*> _list;
    QString _request;
    float totalBuy;
    float totalPrice;
};

#endif // SYMBOLSLISTS_H
