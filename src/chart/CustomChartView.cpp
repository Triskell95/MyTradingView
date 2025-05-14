#include "customchartview.h"
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QDateTime>

CustomChartView::CustomChartView(QChart* chart, QWidget* parent)
    : QChartView(chart, parent)
{
    setMouseTracking(true);

    // Lignes
    _hLine = new QGraphicsLineItem();
    _hLine->setPen(QPen(Qt::white));
    chart->scene()->addItem(_hLine);

    _vLine = new QGraphicsLineItem();
    _vLine->setPen(QPen(Qt::white));
    chart->scene()->addItem(_vLine);

    // Texte des coordonnées
    _coordLabel = new QGraphicsSimpleTextItem();
    _coordLabel->setBrush(Qt::white);
    chart->scene()->addItem(_coordLabel);
}

void CustomChartView::mouseMoveEvent(QMouseEvent* event)
{
    QChart* chart = this->chart();
    if (!chart)
        return;

    // Cast explicite des axes
    QValueAxis* axisY = qobject_cast<QValueAxis*>(chart->axisY());
    QDateTimeAxis* axisX = qobject_cast<QDateTimeAxis*>(chart->axisX());

    if (!axisX || !axisY)
        return;

    QPointF chartPos = chart->mapToValue(event->pos());

    // Lignes verticales et horizontales
    QPointF top = chart->mapToPosition(QPointF(chartPos.x(), axisY->max()));
    QPointF bottom = chart->mapToPosition(QPointF(chartPos.x(), axisY->min()));
    _vLine->setLine(QLineF(top, bottom));

    QPointF left = chart->mapToPosition(QPointF(axisX->min().toMSecsSinceEpoch(), chartPos.y()));
    QPointF right = chart->mapToPosition(QPointF(axisX->max().toMSecsSinceEpoch(), chartPos.y()));
    _hLine->setLine(QLineF(left, right));

    // Texte de coordonnées
    QDateTime dt = QDateTime::fromMSecsSinceEpoch(chartPos.x());
    QString label = QString("X: %1\nY: %2")
                        .arg(dt.toString("dd/MM/yyyy"))
                        .arg(chartPos.y(), 0, 'f', 2);

    _coordLabel->setText(label);
    _coordLabel->setPos(event->pos() + QPoint(10, -30));

    QChartView::mouseMoveEvent(event);
}
