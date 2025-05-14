#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>

class CustomChartView : public QChartView {
    Q_OBJECT

public:
    CustomChartView(QChart* chart, QWidget* parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QGraphicsLineItem* _hLine;
    QGraphicsLineItem* _vLine;
    QGraphicsSimpleTextItem* _coordLabel;
};
