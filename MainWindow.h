// Created by owen on 19/10/21.

#ifndef QT5_CLICK_SHAPES_MAINWINDOW_H
#define QT5_CLICK_SHAPES_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStyle>
#include <QMainWindow>

#include "ClickShapeWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void clearAllObjects();

private:
    void setupUiAndSignals(QWidget *parent);
    QWidget *containerWidget;
    QPushButton *clearButton;
    ClickShapeWidget *canvas;
};
#endif //QT5_CLICK_SHAPES_MAINWINDOW_H
