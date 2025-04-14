#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MyTradingView");
    setSheetStyle();

    showMaximized();

    customPlot = new QCustomPlot();
    chartManager = new ChartManager(customPlot);  // Gestionnaire de graphiques
    dataHandler = new OHLCData();  // Gestion des données OHLC
    apiClient = new ApiClient();  // Client API

    // Exemple de récupération des données via l'API
    QUrl url("https://api.coingecko.com/api/v3/coins/bitcoin/ohlc?vs_currency=usd&days=365");
    apiClient->fetchOHLCData(url);

    // Traitement des données dans le module `data`
    dataHandler->processData(ohlcData);

    // Affichage des données traitées dans le graphique via `chart`
    chartManager->plotData(ohlcData);

    // Réaffichage du graphique
    customPlot->replot();
/*
    customPlot = new QCustomPlot();
    setCentralWidget(customPlot);

    ApiClient *apiClient = new ApiClient(this);
    connect(apiClient, &ApiClient::dataFetched, this, &MainWindow::onDataFetched);

    // Requête vers CoinGecko
    QUrl url("https://api.coingecko.com/api/v3/coins/bitcoin/ohlc?vs_currency=usd&days=365");
    apiClient->fetchOHLCData(url);
*/
/*
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onReplyFinished);

    // Requête vers CoinGecko
    QUrl url("https://api.coingecko.com/api/v3/coins/bitcoin/ohlc?vs_currency=usd&days=365");
    manager->get(QNetworkRequest(url));
    */
    /*
    QCustomPlot *customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    QVector<double> x{1, 2, 3, 4, 5};
    QVector<double> y{10, 20, 15, 25, 20};

    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("Temps");
    customPlot->yAxis->setLabel("Valeur");
    customPlot->rescaleAxes();
    customPlot->replot();
    */

    //setWindowIcon(QIcon(":/resources/logo.png"));  // Remplace le chemin par celui de ton icône
}
/*
void MainWindow::onDataFetched(const QByteArray &data) {
    QJsonDocument json = QJsonDocument::fromJson(data);
    if (json.isArray()) {
        QJsonArray arr = json.array();
        OHLCData ohlcData;
        ohlcData.fromJsonArray(arr);

        ChartManager chartManager(customPlot);
        chartManager.setupAxes();
        chartManager.plotCandlesticks(ohlcData.xData, ohlcData.openData, ohlcData.highData,
                                      ohlcData.lowData, ohlcData.closeData);
    }
}*/
/*
void MainWindow::onReplyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    if (json.isArray()) {
        QJsonArray arr = json.array();
        drawCandlesticks(arr);
    }
    reply->deleteLater();
}
*/
/*
void MainWindow::drawCandlesticks(const QJsonArray &data)
{
    customPlot->clearGraphs();  // Nettoie les anciens graphiques

    // Configuration des axes X et Y
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd/MM/yy");
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->xAxis->setLabel("Jour");
    customPlot->yAxis->setLabel("Prix (USD)");

    QVector<double> xData, openData, highData, lowData, closeData;

    // Récupération des données OHLC
    for (int i = 0; i < data.size(); ++i) {
        QJsonArray ohlc = data[i].toArray();
        qint64 timestamp = ohlc[0].toVariant().toLongLong() / 1000;
        double open = ohlc[1].toDouble();
        double high = ohlc[2].toDouble();
        double low = ohlc[3].toDouble();
        double close = ohlc[4].toDouble();

        xData.append(timestamp);
        openData.append(open);
        highData.append(high);
        lowData.append(low);
        closeData.append(close);
    }

    // Créer un graphique pour les bougies en utilisant QCPGraph
    QCPGraph *candlesticksGraph = customPlot->addGraph();
    QVector<double> highPoints, lowPoints;

    // Remplir les vecteurs pour les points hauts et bas
    for (int i = 0; i < data.size(); ++i) {
        highPoints.append(highData[i]);
        lowPoints.append(lowData[i]);
    }

    // Ajouter les données à la courbe (graphique)
    candlesticksGraph->setData(xData, closeData);  // Ajoute les données de fermeture

    // Ajouter un graphique pour les lignes hautes/basses
    customPlot->addGraph();
    customPlot->graph(1)->setData(xData, highPoints);  // Données hautes
    customPlot->graph(1)->setPen(QPen(Qt::green));  // Couleur pour la ligne haute
    customPlot->graph(1)->setName("High Prices");

    customPlot->addGraph();
    customPlot->graph(2)->setData(xData, lowPoints);  // Données basses
    customPlot->graph(2)->setPen(QPen(Qt::red));  // Couleur pour la ligne basse
    customPlot->graph(2)->setName("Low Prices");

    // Configuration des axes et mise à l'échelle automatique
    customPlot->xAxis->rescale(true);
    customPlot->yAxis->rescale(true);
    customPlot->replot();  // Rafraîchit l'affichage
}*/

/*void MainWindow::on_plotButton_clicked()
{
    // Implémentez ce que vous voulez faire lorsque le bouton est cliqué
    qDebug() << "Plot button clicked!";
}*/

void MainWindow::setSheetStyle()
{
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #2b3a4d;
            border: 1px solid #1d2b3a;
        }
        QMenuBar {
            background-color: #283241;
            color: white;
        }
        QMenuBar::item {
            padding: 5px 15px;
        }
        QMenuBar::item:selected {
            background-color: #3c4e65;
        }
        QToolBar {
            background-color: #283241;
            border: none;
        }
        QPushButton {
            background-color: #405060;
            color: white;
            border: 1px solid #3c4e65;
            border-radius: 5px;
            padding: 5px 10px;
        }
        QPushButton:hover {
            background-color: #5f7587;
        }
        QPushButton:pressed {
            background-color: #4a616d;
        }
        QLineEdit, QTextEdit {
            background-color: #3c4e65;
            color: white;
            border: 1px solid #3c4e65;
            padding: 5px;
        }
        QScrollBar:vertical, QScrollBar:horizontal {
            background: #283241;
            width: 12px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
            background: #4a5a6b;
            border-radius: 6px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: #283241;
            border: none;
        }
        QTabWidget::pane {
            border: 1px solid #1d2b3a;
        }
        QTabBar::tab {
            background-color: #2b3a4d;
            color: white;
            padding: 5px;
            border: 1px solid #1d2b3a;
        }
        QTabBar::tab:selected {
            background-color: #3c4e65;
        }
        QStatusBar {
            background-color: #2b3a4d;
            color: white;
        }
    )");
}

MainWindow::~MainWindow()
{
    delete ui;
}
