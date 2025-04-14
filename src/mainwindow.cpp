#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MyTradingView");

    setStyleSheet(R"(
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

    showMaximized();

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

    //setWindowIcon(QIcon(":/resources/logo.png"));  // Remplace le chemin par celui de ton icône
}

MainWindow::~MainWindow()
{
    delete ui;
}
