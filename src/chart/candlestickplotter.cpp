// chart/CandlestickPlotter.cpp
#include "CandlestickPlotter.h"

CandlestickPlotter::CandlestickPlotter(QCustomPlot* plotWidget) : plotWidget(plotWidget) {}

void CandlestickPlotter::plot(const QVector<double>& xData, const QVector<double>& openData,
                              const QVector<double>& highData, const QVector<double>& lowData,
                              const QVector<double>& closeData) {

    if (xData.isEmpty() || openData.isEmpty() || highData.isEmpty() || lowData.isEmpty() || closeData.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Les données sont vides");
        msgBox.setIcon(QMessageBox::Critical);  // Définir l'icône comme erreur
        msgBox.setStandardButtons(QMessageBox::Ok);  // Ajouter un bouton "OK"
        msgBox.exec();  // Afficher la boîte de message modale
        return;
    }

    QCPBars *candlestickBars = new QCPBars(plotWidget->xAxis, plotWidget->yAxis);
    candlestickBars->setWidth(0.8);
    candlestickBars->setData(xData, closeData);
    candlestickBars->setPen(Qt::NoPen);
}
