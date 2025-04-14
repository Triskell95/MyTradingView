#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCustomPlot.h>
#include "chart/chartmanager.h"
#include "data/ohlcdata.h"
#include "api/apiclient.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    QCustomPlot* customPlot;
    Ui::MainWindow *ui;
    ChartManager *chartManager;  // Instance de ChartManager pour gérer l'affichage des graphiques
    OHLCData* dataHandler;
    QVector<OHLCData> ohlcData;  // Conteneur pour stocker les données OHLC
    ApiClient* apiClient;

    // Méthode pour initialiser les données de test (OHLC)
    void initializeTestData();
    void setSheetStyle();
};

#endif // MAINWINDOW_H
