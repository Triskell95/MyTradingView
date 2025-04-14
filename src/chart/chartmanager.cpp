#include "chartmanager.h"
#include "qcustomplot.h"

ChartManager::ChartManager(QObject *parent) : QObject(parent)
{
    customPlot = new QCustomPlot();

    // Initialisation du graphique
    customPlot->addGraph();
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setPen(QPen(Qt::black));

    customPlot->setBackground(QBrush(Qt::transparent));
    // Rendre les axes également transparents (si nécessaire)
    customPlot->xAxis->setBasePen(QPen(Qt::white));  // Axe X transparent
    customPlot->yAxis->setBasePen(QPen(Qt::white));  // Axe Y transparent
    customPlot->xAxis->setTickPen(QPen(Qt::white));  // Marqueurs d'axe X transparents
    customPlot->yAxis->setTickPen(QPen(Qt::white));  // Marqueurs d'axe Y transparents
    customPlot->xAxis->setSubTickPen(QPen(Qt::white));  // Sous-marques X
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));  // Sous-marques Y
    customPlot->xAxis->setTickLabelColor(Qt::white);  // Couleur des labels de l'axe X (si vous souhaitez les afficher)
    customPlot->yAxis->setTickLabelColor(Qt::white);  // Couleur des labels de l'axe Y (si vous souhaitez les afficher)


    // Création de l'objet QCPFinancial uniquement ici
    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    candlesticks->setWidth(0.6);  // Paramètre pour afficher les bougies
}

QCustomPlot *ChartManager::getPlot()
{
    return customPlot;
}

void ChartManager::plotCandlesticks(const QList<OHLCData> &data)
{
    QVector<double> timeStamps;
    QVector<double> opens;
    QVector<double> highs;
    QVector<double> lows;
    QVector<double> closes;

    for (const OHLCData &ohlc : data)
    {
        // Remplir les vecteurs avec les valeurs OHLC
        timeStamps.append(ohlc.timestamp);
        opens.append(ohlc.open);
        highs.append(ohlc.high);
        lows.append(ohlc.low);
        closes.append(ohlc.close);
    }

    // Passer les données sous forme de vecteurs séparés à setData
    candlesticks->setData(timeStamps, opens, highs, lows, closes);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd/MM/yyyy");
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->xAxis->setRange(timeStamps.first(), timeStamps.last());  // Plage d'axe X entre le premier et le dernier timestamp
    customPlot->yAxis->rescale();  // Redimensionner l'axe Y pour s'adapter aux données
    customPlot->replot();
}
