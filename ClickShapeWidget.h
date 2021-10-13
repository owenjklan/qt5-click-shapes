//
// Created by owen on 13/10/21.
//

#ifndef QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
#define QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H

#include <QWidget>
#include <QPushButton>

class ClickShapeWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClickShapeWidget(QWidget *parent = 0);
    ~ClickShapeWidget();

private slots:
    void onCanvasClick();

private:
    void setupUiAndSignals(QWidget *parent);

    QPushButton *button;
    QWidget *canvas;
};


#endif //QT5_CLICK_SHAPES_CLICKSHAPEWIDGET_H
