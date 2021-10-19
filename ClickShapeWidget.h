// Created by owen on 13/10/21.

#ifndef QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
#define QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H

#include <QPen>
#include <QBrush>

#include <QWidget>
#include <QPushButton>


#define RED "\033[33;1m"
#define NORMAL "\033[0m"

#define MIN_RECT_WIDTH 48
#define MIN_RECT_HEIGHT 32
#define MAX_RECT_WIDTH 192
#define MAX_RECT_HEIGHT 128

class ClickShapeWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClickShapeWidget(QWidget *parent = nullptr);
    void addShape(QPoint at);

    void paintEvent(QPaintEvent *event) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:

private:
    void increaseNewSize();
    void decreaseNewSize();

    QList<QRect *> placements;

    int newWidth = 96;
    int newHeight = 64;
};
#endif //QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
