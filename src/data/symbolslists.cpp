#include "SymbolsLists.h"

#include <QHeaderView>
#include "filemanager.h"
#include "api/apiclient.h"
#include <QStandardPaths>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>

SymbolsLists::SymbolsLists(QString filename)
{
    // Load symbols list
    FileManager fm = FileManager();
    _list = fm.loadSymbols(filename);
    sortList();

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(colIndex::max);
    tableWidget->setHorizontalHeaderLabels({"Symbol", "Price", "Var"});

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

    // tableWidget need to be initialised first !
    loadSymbols();

    ApiClient* api = new ApiClient();

    QString apiKey = fm.loadFinnhubKey();

    if(apiKey == "")
    {
        bool ok = false;
        apiKey = QInputDialog::getText(nullptr,
                                             "Clé Finnhub manquante",
                                             "Entrez votre clé Finnhub:",
                                             QLineEdit::Normal,
                                             "",  // valeur par défaut
                                             &ok);
    }

    api->fetchFinnhubQuote("AAPL", apiKey, [](QJsonObject quote) {
        qDebug() << "Prix actuel:" << quote["c"].toDouble();  // "c" = current price
        qDebug() << "Ouverture:" << quote["o"].toDouble();   // "o" = open
        qDebug() << "Haut jour:" << quote["h"].toDouble();   // "h" = high
        qDebug() << "Bas jour:" << quote["l"].toDouble();    // "l" = low
    });


    api->fetchYahooQuotes(_list, [=](QList<Symbol*> fetchedSymbols){
        // Callback, cette fonction sera appelée une fois les données récupérées
        qDebug() << "Données récupérées : ";
        for (Symbol* symbol : fetchedSymbols) {
            qDebug() << "Symbol: " << symbol->getSymbol() << ", Price: " << symbol->getPrice();
        }
    });
}

void SymbolsLists::loadSymbols()
{
    for(auto& s : _list)
    {
        addSymbol(s);
    }
}

void SymbolsLists::addSymbol(Symbol* s)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    tableWidget->setItem(row, colIndex::label, new QTableWidgetItem(QString("%1 (%2)").arg(s->getLabel()).arg(s->getSymbol()) ));
    tableWidget->item(row, colIndex::label)->setForeground(QBrush(Qt::white));
    //tableWidget->item(row, colIndex::label)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    tableWidget->setItem(row, colIndex::price, new QTableWidgetItem(QString("%1 %2").arg(s->getPrice(), 0, 'f', 2).arg(s->getCurrency()) ));
    tableWidget->item(row, colIndex::price)->setForeground(QBrush(Qt::white));
    tableWidget->item(row, colIndex::price)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    tableWidget->setItem(row, colIndex::var, new QTableWidgetItem( QString("%1 \%").arg(s->getDailyVar(), 0, 'f', 2) ));
    if(s->getDailyVar() >= 0)
        tableWidget->item(row, colIndex::var)->setForeground(QBrush(Qt::green));
    else
        tableWidget->item(row, colIndex::var)->setForeground(QBrush(Qt::red));
    tableWidget->item(row, colIndex::var)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

void SymbolsLists::sortList()
{
    std::sort(_list.begin(), _list.end());  // nécessite que operator< soit redéfini
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
