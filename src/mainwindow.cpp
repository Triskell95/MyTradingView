#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/ohlcdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    chartManager(new ChartManager(this)),
    apiClient(new ApiClient(this)),
    symbols(new SymbolsLists())
{
    ui->setupUi(this);

    ui->horizontalLayout->addWidget(chartManager->getPlot(), 7);
    ui->horizontalLayout->addWidget(symbols->getTable(), 3);
    ui->tab_chart->setLayout(ui->horizontalLayout);
    setCentralWidget(ui->tabWidget);

    setSheetStyle();

    showMaximized();
}

void MainWindow::on_plotButton_clicked() {
    apiClient->fetchOHLC("bitcoin", [=](const QList<OHLCData> &ohlcList) {

        if(!ohlcList.empty())
        {
            chartManager->plotCandlesticks(ohlcList);
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erreur");
            msgBox.setText("Les données sont vides");
            msgBox.setIcon(QMessageBox::Critical);  // Définir l'icône comme erreur
            msgBox.setStandardButtons(QMessageBox::Ok);  // Ajouter un bouton "OK"
            msgBox.exec();  // Afficher la boîte de message modale
        }
    });
}

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
