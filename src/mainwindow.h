#pragma once

#include <QMainWindow>
#include "chart/chartmanager.h"
#include "api/apiclient.h"
#include "data/symbolslists.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow* ui;
    ChartManager* chartManager;
    ApiClient* apiClient;
    SymbolsLists* symbols;
    SymbolsLists* positions;

    void setSheetStyle();
};
