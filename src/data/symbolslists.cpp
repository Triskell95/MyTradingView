#include "SymbolsLists.h"

#include <QHeaderView>

SymbolsLists::SymbolsLists()
{
    Symbol* s1 = new Symbol("Intel", "INTC", typeSymbol::stockUS, 20.01, -1.367);
    Symbol* s2 = new Symbol("Air Liquide", "EPA:AI", typeSymbol::stockFR, 170.45, 2.154);
    Symbol* s3 = new Symbol("Bitcoin", "BTC", typeSymbol::crypto, 83456.1235, 2.4553);
    _list.append(s1);
    _list.append(s2);
    _list.append(s3);
    sortList();

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(colIndex::max);
    tableWidget->setHorizontalHeaderLabels({"Symbol", "Price", "Var"});

   // tableWidget->setStyleSheet("background: transparent;");
    tableWidget->setAttribute(Qt::WA_TranslucentBackground);
    tableWidget->viewport()->setAutoFillBackground(false);
    tableWidget->setStyleSheet(R"(
        QTableWidget {
            background: transparent;
            border: transparent
            color: white;
            gridline-color: transparent;
        }
        QHeaderView::section {
            background-color: transparent;
            color: white;
            border: transparent;
        }
        QTableWidget::item {
            color: white;
            background-color: transparent;
        }
    )");
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(tableWidget, &QTableWidget::cellClicked, this, &SymbolsLists::onCellClicked);

    addSymbol(s1);
    addSymbol(s2);
    addSymbol(s3);
}

void SymbolsLists::addSymbol(Symbol* s)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    tableWidget->setItem(row, colIndex::label, new QTableWidgetItem(s->getLabel()));
    tableWidget->item(row, colIndex::label)->setForeground(QBrush(Qt::white));

    tableWidget->setItem(row, colIndex::price, new QTableWidgetItem(QString("%1 %2").arg(s->getPrice(), 0, 'f', 2).arg(s->getCurrency()) ));
    tableWidget->item(row, colIndex::price)->setForeground(QBrush(Qt::white));

    tableWidget->setItem(row, colIndex::var, new QTableWidgetItem( QString("%1 \%").arg(s->getDailyVar(), 0, 'f', 2) ));
    if(s->getDailyVar() >= 0)
        tableWidget->item(row, colIndex::var)->setForeground(QBrush(Qt::green));
    else
        tableWidget->item(row, colIndex::var)->setForeground(QBrush(Qt::red));
}

void SymbolsLists::sortList()
{
    std::sort(_list.begin(), _list.end());  // nécessite que operator< soit défini
}

void SymbolsLists::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    int total = tableWidget->viewport()->width();
    tableWidget->setColumnWidth(0, total * 0.6);
    tableWidget->setColumnWidth(1, total * 0.2);
    tableWidget->setColumnWidth(2, total * 0.2);
}

void SymbolsLists::onCellClicked(int row, int column)
{
    QTableWidgetItem *item = tableWidget->item(row, column);
    if (item)
        qDebug() << "Cellule cliquée :" << item->text();
}
