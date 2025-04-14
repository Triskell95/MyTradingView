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

    inline QTableWidget* getTable() { return tableWidget; };

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onCellClicked(int row, int column);

private:
    QTableWidget *tableWidget;
    QList<Symbol*> _list;
};

#endif // SYMBOLSLISTS_H
