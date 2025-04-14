#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <QCustomPlot.h>  // Bibliothèque pour gérer les graphiques
#include <QVector>
#include "data/ohlcdata.h"  // Inclure les données OHLC

class ChartManager
{
public:
    // Constructeur
    ChartManager(QCustomPlot *customPlotWidget);

    // Méthode pour afficher les données OHLC sur le graphique
    void plotData(const QVector<OHLCData> &ohlcData);

    // Méthode pour configurer l'axe Y
    void configureYAxis();

    // Méthode pour configurer l'axe X
    void configureXAxis();

private:
    QCustomPlot *customPlot;  // Pointeur vers l'objet QCustomPlot
    QCPGraph *ohlcGraph;     // Graphique pour afficher les données OHLC
    QVector<double> xData;   // Vecteur des données pour l'axe X
    QVector<double> openData;    // Vecteur des valeurs d'ouverture des données OHLC
    QVector<double> highData;    // Vecteur des valeurs maximales des données OHLC
    QVector<double> lowData;     // Vecteur des valeurs minimales des données OHLC
    QVector<double> closeData;   // Vecteur des valeurs de clôture des données OHLC
};

#endif // CHARTMANAGER_H
