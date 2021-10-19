// Created by owen on 19/10/21.

#include <QCloseEvent>
#include <QDebug>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "ClickShapeWidget.h"

MainWindow::MainWindow(QWidget *parent) {
    setupUiAndSignals(parent);
}

void MainWindow::setupUiAndSignals(QWidget *parent) {
    refreshButton = new QPushButton("&Refresh");
    canvas = new ClickShapeWidget(parent);
    canvas->setStyleSheet("background-color: #BEB69F;");

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(refreshButton);
    layout->addWidget(canvas);

    setLayout(layout);
    setWindowTitle("Qt5 Click Shapes");

    connect(refreshButton, SIGNAL(released()),
            this, SLOT(refreshRequested()));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "closeEvent()";
    event->accept();

    // Otherwise...
    // event->ignore();
}

void MainWindow::refreshRequested() {
    qDebug() << "Refresh button has been pressed.";
}