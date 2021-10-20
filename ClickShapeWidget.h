// Created by owen on 13/10/21.

#ifndef QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
#define QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H

#include <QPen>
#include <QBrush>
#include <QWidget>
#include <QStack>
#include <QPushButton>
#include <QShortcut>

#include "CustomObj.h"

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
    void clearShapes();
    void paintEvent(QPaintEvent *event) override;
    int redoCount();
    void enableConnectMode();
    void enablePlaceMode();
public slots:

    void selectAll(bool checked = false);
    void unselectAll(bool checked = false);
    void invertSelection(bool checked = false);
    void setCurrentName(QString newName);
    void popPlacement(bool checked = false);
    void addPlacementFromRedoList(bool checked = false);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void increaseNewSize();
    void decreaseNewSize();
    CustomObj *findSelectedObj(QPoint);

    QString currentName;
    QList<CustomObj *> placements;
    QStack<CustomObj *> redoList;

#define CONNECT_MODE 0
#define PLACE_MODE 1
    int mode = CONNECT_MODE;

    int newWidth = 96;
    int newHeight = 64;
};
#endif //QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
