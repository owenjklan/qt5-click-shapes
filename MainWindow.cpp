// Created by owen on 19/10/21.

#include <QCloseEvent>
#include <QDebug>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "ClickShapeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    setupUiAndSignals(parent);

    QFile file("../style.css");
    file.open(QFile::ReadOnly);
    QString styleString = file.readAll();
    setStyleSheet(styleString);
}

void MainWindow::setupUiAndSignals(QWidget *parent) {
    refreshButton = new QPushButton("&Refresh");
    refreshButton->setMaximumWidth(150);
    canvas = new ClickShapeWidget(parent);

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