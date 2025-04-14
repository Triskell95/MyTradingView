#include "chartmanager.h"
#include <QCustomPlot.h>
//#include <QCPBars.h>  // Pour dessiner les barres de données
//#include <QCPGraph.h>  // Pour dessiner un graphique de données linéaires
#include <QVector>

ChartManager::ChartManager(QCustomPlot *customPlotWidget)
    : customPlot(customPlotWidget)
{
    // Configuration initiale du graphique
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);  // Autoriser le zoom et le déplacement du graphique

    // Configure les axes
    configureXAxis();
    configureYAxis();
}

void ChartManager::configureXAxis()
{

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd/MM/yy");

    customPlot->xAxis->setTicker(dateTicker);
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Price (USD)");
    customPlot->xAxis->setRange(0, 10);  // Définir une plage d'exemple
}

void ChartManager::configureYAxis()
{
    customPlot->yAxis->setLabel("Price");
    customPlot->yAxis->setRange(0, 100);  // Plage d'exemple pour les prix
}

void ChartManager::plotData(const QVector<OHLCData> &ohlcData)
{
    // Vider les anciens vecteurs
    xData.clear();
    openData.clear();
    highData.clear();
    lowData.clear();
    closeData.clear();

    // Remplir les vecteurs avec les nouvelles données OHLC
    for (const OHLCData &ohlc : ohlcData) {
        xData.append(ohlc.xData);  // L'axe X représente le temps
        openData.append(ohlc.openData);
        highData.append(ohlc.highData);
        lowData.append(ohlc.lowData);
        closeData.append(ohlc.closeData);
    }

    // Ajouter un graphique pour les barres OHLC
    customPlot->clearGraphs();  // Effacer les anciens graphiques
    customPlot->addGraph();  // Ajouter un nouveau graphique

    // Tracer les données OHLC sur le graphique
    QCPGraph *ohlcGraph = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    ohlcGraph->setData(xData, closeData);  // Afficher les prix de clôture sur l'axe Y

    // Tracer d'autres séries si nécessaire (par exemple, les prix d'ouverture, de haut et de bas)
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars->setData(xData, openData);  // Afficher les prix d'ouverture sous forme de barres

    customPlot->replot();  // Redessiner le graphique
}
