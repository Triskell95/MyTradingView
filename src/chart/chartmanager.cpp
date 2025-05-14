#include "chartmanager.h"

ChartManager::ChartManager(QObject *parent) : QObject(parent)
{
    _series = new QCandlestickSeries();
    _chart = new QChart();
    setStyle();

    // Création de la vue du graphique
    _chartView = new CustomChartView(_chart);
}

void ChartManager::setStyle()
{
    // Création de la série de chandeliers
    _series->setName("BTCUSD");
    _series->setIncreasingColor(Qt::green);
    _series->setDecreasingColor(Qt::red);

    _chart->addSeries(_series);
    _chart->setTitle("BTC_USD");         // Titre du graphique
    _chart->legend()->hide();        // On cache la légende (optionnel)
    _chart->setBackgroundBrush(Qt::NoBrush);       // Pas de brosse = transparent
    _chart->setBackgroundPen(Qt::NoPen);           // Pas de bordure
    _chart->setMargins(QMargins(20, 20, 20, 20));

    // Axe X : axe temporel (en dates)
    _axisX = new QDateTimeAxis;
    _axisX->setMin(QDateTime::fromMSecsSinceEpoch(_minTime));
    _axisX->setMax(QDateTime::fromMSecsSinceEpoch(_maxTime));
    _axisX->setFormat("dd/MM/yyyy");     // Format d'affichage des dates sur l'axe
    _axisX->setTitleText("Date");
    _axisX->setTitleBrush(Qt::white);
    _axisX->setLabelsColor(Qt::white);
    _axisX->setLinePen(QPen(Qt::white));
    _axisX->setGridLinePen(QPen(Qt::lightGray));
    _axisX->setTickCount(6);
    _chart->addAxis(_axisX, Qt::AlignBottom);
    _series->attachAxis(_axisX);     // Lier la série à l'axe X

    // Axe Y : valeurs de prix
    _axisY = new QValueAxis;
    _axisY->setMin(_minPrice);
    _axisY->setMax(_maxPrice);
    _axisY->setTitleText("Prix");
    _axisY->setTitleBrush(Qt::white);
    _axisY->setLabelsColor(Qt::white);
    _axisY->setLinePen(QPen(Qt::white));
    _axisY->setGridLinePen(QPen(Qt::darkGray));
    _axisY->setTickCount(6);
    _chart->addAxis(_axisY, Qt::AlignLeft);
    _series->attachAxis(_axisY);     // Lier la série à l'axe Y
}

void ChartManager::setChartView()
{
    // Création de la vue du graphique
    _chartView->setChart(_chart);
    _chartView->setStyleSheet("background: transparent");
    _chartView->setAttribute(Qt::WA_TranslucentBackground);
    _chartView->setRenderHint(QPainter::Antialiasing);

    //_chartView->setRubberBand(QChartView::RectangleRubberBand); // Zoom
    //_chartView->setDragMode(QGraphicsView::ScrollHandDrag);     // Déplacement
}

void ChartManager::setChartData(const QList<OHLCData> &ohlcList)
{
    _series->clear();

    // Reset axis
    _minPrice = std::numeric_limits<qreal>::max();
    _maxPrice = std::numeric_limits<qreal>::min();
    _minTime = QDateTime::currentMSecsSinceEpoch();
    _maxTime = QDateTime::currentMSecsSinceEpoch();

    // Remplissage de la série avec les données OHLC
    for (const OHLCData &data : ohlcList) {
        qint64 msTimestamp = data.timestamp * 1000; // Qt utilise des millisecondes
        auto *set = new QCandlestickSet(data.open, data.high, data.low, data.close, msTimestamp);
        _series->append(set);
        _minPrice = std::min(_minPrice, set->low());
        _maxPrice = std::max(_maxPrice, set->high());
        if(data.open > 0)
        {
            _minTime  = std::min(_minTime, msTimestamp);
            _maxTime  = std::max(_maxTime, msTimestamp);
        }
    }

    qreal padding = (_maxPrice - _minPrice) * 0.05;
    _minPrice -= padding;
    _maxPrice += padding;

    _minPrice = std::floor(_minPrice / 100.0) * 100;
    _maxPrice = std::ceil(_maxPrice / 100.0) * 100;

    // Axe X : axe temporel (en dates)
    _axisX->setMin(QDateTime::fromMSecsSinceEpoch(_minTime));
    _axisX->setMax(QDateTime::fromMSecsSinceEpoch(_maxTime));
    _axisX->setFormat("dd/MM/yyyy");     // Format d'affichage des dates sur l'axe
    _axisX->setTitleText("Date");

    _axisY->setMin(_minPrice);
    _axisY->setMax(_maxPrice);
    _axisY->setTitleText("Prix");
}

