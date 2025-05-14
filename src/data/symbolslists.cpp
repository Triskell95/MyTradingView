#include "SymbolsLists.h"

#include <QHeaderView>
#include "filemanager.h"
#include "api/apiclient.h"
#include <QStandardPaths>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>

SymbolsLists::SymbolsLists(QString filename): totalBuy(0.0), totalPrice(0.0)
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

    while(apiKey == "")
    {
        bool ok = false;
        apiKey = QInputDialog::getText(nullptr,
                                             "Clé Finnhub manquante",
                                             "Entrez votre clé Finnhub:",
                                             QLineEdit::Normal,
                                             "",  // valeur par défaut
                                             &ok);
        fm.saveFinnhubKey(apiKey);
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
    totalBuy = 0.0;
    totalPrice = 0.0;
    for(auto& s : _list)
    {
        addSymbol(s);
        totalBuy    += s->getBuyPrice();
        totalPrice += s->getPrice();
    }
}

void SymbolsLists::fillQTableView(QTableView* table, QStandardItemModel* model)
{

    //LABEL = 0, NB, BUY, PRICE, VAR, REPART, TYPE, MAX

    model->setHeaderData(colPosition::LABEL, Qt::Horizontal, "Nom");
    model->setHeaderData(colPosition::NB, Qt::Horizontal,    "Nombre");
    model->setHeaderData(colPosition::BUY, Qt::Horizontal,   "Prix d'achat");
    model->setHeaderData(colPosition::TOTAL_INVEST, Qt::Horizontal, "Total Investi");
    model->setHeaderData(colPosition::PRICE, Qt::Horizontal, "Prix actuel");
    model->setHeaderData(colPosition::TOTAL_VAL, Qt::Horizontal, "Valeur Totale");
    model->setHeaderData(colPosition::VAR, Qt::Horizontal,   "Variation");
    model->setHeaderData(colPosition::REPART, Qt::Horizontal,"Répartition");
    model->setHeaderData(colPosition::TYPE, Qt::Horizontal,  "Type");

    table->reset();
    for(int i = 0; i < _list.count(); i++)
    {
        QStandardItem* label = new QStandardItem(_list[i]->getLabel());
        model->setItem(i, colPosition::LABEL, label);

        QStandardItem* nb = new QStandardItem(QString::number(_list[i]->getNb(), 'f', 2));
        nb->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        model->setItem(i, colPosition::NB, nb);

        QStandardItem* buy = new QStandardItem(QString::number(_list[i]->getBuyPrice(), 'f', 2));
        buy->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        model->setItem(i, colPosition::BUY, buy);

        QStandardItem* totBuy = new QStandardItem(QString::number(_list[i]->getBuyPrice() * _list[i]->getNb(), 'f', 2));
        totBuy->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        model->setItem(i, colPosition::TOTAL_INVEST, totBuy);

        QStandardItem* price = new QStandardItem(QString::number(_list[i]->getPrice(), 'f', 2));
        price->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        model->setItem(i, colPosition::PRICE, price);

        QStandardItem* totPrice = new QStandardItem(QString::number(_list[i]->getPrice() * _list[i]->getNb(), 'f', 2));
        totPrice->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        model->setItem(i, colPosition::TOTAL_VAL, totPrice);

        float fVar = (_list[i]->getPrice() / _list[i]->getBuyPrice() - 1) * 100.0;
        QString strVar = QString("%1 %").arg(fVar, 0, 'f', 2);
        QStandardItem* var = new QStandardItem(strVar);
        var->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        fVar >= 0 ? var->setForeground(QBrush(Qt::green)) : var->setForeground(QBrush(Qt::red));
        model->setItem(i, colPosition::VAR, var);

        float fRepart = _list[i]->getPrice() / totalPrice * 100;
        QString strRepart = QString("%1 %").arg(fRepart, 0, 'f', 2);
        QStandardItem* repart = new QStandardItem(strRepart);
        repart->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        fRepart >= 0 ? repart->setForeground(QBrush(Qt::green)) : repart->setForeground(QBrush(Qt::red));
        model->setItem(i, colPosition::REPART, repart);

        QStandardItem* strType = new QStandardItem(_list[i]->getStrType());
        model->setItem(i, colPosition::TYPE, strType);

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
