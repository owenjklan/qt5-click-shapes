// Created by owen on 19/10/21.

#ifndef QT5_CLICK_SHAPES_MAINWINDOW_H
#define QT5_CLICK_SHAPES_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>

#include "ClickShapeWidget.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUiAndSignals(QWidget *parent);
    void refreshRequested();

    QPushButton *refreshButton;
    ClickShapeWidget *canvas;
};
#endif //QT5_CLICK_SHAPES_MAINWINDOW_H
