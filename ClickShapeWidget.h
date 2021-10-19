// Created by owen on 13/10/21.

#ifndef QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
#define QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H

#include <QPen>
#include <QBrush>

#include <QWidget>
#include <QPushButton>

class ClickShapeWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClickShapeWidget(QWidget *parent = nullptr);
    ~ClickShapeWidget();
    void addShape(QPoint at);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:

private:
    void setupUiAndSignals(QWidget *parent);
    void setupPainter();
    void paintShapes();

    QList<QPoint> placements;

    QPushButton *button;
    QWidget *canvas;
    QPoint lastClickPoint;

    QPen paintPen;
    QBrush paintBrush;
};
#endif //QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
