#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/ohlcdata.h"
#include <QMessageBox>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    chartManager(new ChartManager(this)),
    apiClient(new ApiClient(this)),
    symbols(new SymbolsLists("symbols")),
    positions(new SymbolsLists("positions"))
{
    ui->setupUi(this);

    // Tab "chart"
    ui->horizontalLayout->addWidget(chartManager->getChartView(), 7);
    ui->horizontalLayout->addSpacing(20);
    ui->horizontalLayout->addWidget(symbols->getTable(), 3);
    ui->tab_chart->setLayout(ui->horizontalLayout);
    setCentralWidget(ui->tabWidget);

    // Tab "Positions"
    QPalette palette = ui->tablePos->palette();
    palette.setColor(QPalette::Base, Qt::transparent); // Fond transparent
    palette.setColor(QPalette::Text, Qt::white);       // Texte
    ui->tablePos->setPalette(palette);

    QStandardItemModel* model = new QStandardItemModel(0, 0, this); // 0 lignes, 0 colonnes
    ui->tablePos->setModel(model);
    ui->tablePos->setBackgroundRole(QPalette::NoRole);
    model->setColumnCount(colPosition::MAX);
    positions->fillQTableView(ui->tablePos, model);

    setSheetStyle();
    showMaximized();

    // Load by default BTCUSD chart
    apiClient->fetchOHLC("bitcoin", [=](const QList<OHLCData> &ohlcList) {

        if(!ohlcList.empty())
        {
            chartManager->setChartData(ohlcList);
            chartManager->setChartView();
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erreur");
            msgBox.setText("Les données sont vides");
            msgBox.setIcon(QMessageBox::Critical);  // Définir l'icône comme erreur
            msgBox.setStandardButtons(QMessageBox::Ok);  // Ajouter un bouton "OK"
            msgBox.exec();  // Afficher la boîte de message modale
        }
    });

    ui->tabWidget->setCurrentIndex(0);
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
