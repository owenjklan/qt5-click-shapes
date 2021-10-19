// Created by owen on 19/10/21.

#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "ClickShapeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    //  UI and Signals must come before Menus and Actions!
    setupUiAndSignals(parent);
    setupMenusAndActions();

    QFile file("../style.css");
    file.open(QFile::ReadOnly);
    QString styleString = file.readAll();
    setStyleSheet(styleString);
}

void MainWindow::setupMenusAndActions() {
    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));

    unselectAllAction = new QAction(tr("&None"), this);
    unselectAllAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A));

    invertSelectionAction = new QAction(tr("&Invert"), this);
    invertSelectionAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));

    fileMenu = menuBar()->addMenu(tr("&File"));
    selectMenu = menuBar()->addMenu(tr("&Select"));
    selectMenu->addAction(selectAllAction);
    selectMenu->addAction(unselectAllAction);
    selectMenu->addAction(invertSelectionAction);

    connect(selectAllAction, SIGNAL(triggered(bool)),
            canvas, SLOT(selectAll(bool)));
    connect(unselectAllAction, SIGNAL(triggered(bool)),
            canvas, SLOT(unselectAll(bool)));
    connect(invertSelectionAction, SIGNAL(triggered(bool)),
            canvas, SLOT(invertSelection(bool)));
}

void MainWindow::setupUiAndSignals(QWidget *parent) {
    containerWidget = new QWidget(parent);
    clearButton = new QPushButton("&Clear");
    clearButton->setMaximumWidth(150);
    canvas = new ClickShapeWidget(parent);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(clearButton);
    layout->addWidget(canvas);
    containerWidget->setLayout(layout);
    setCentralWidget(containerWidget);
    setWindowTitle("Qt5 Click Shapes");

    connect(clearButton, SIGNAL(released()),
            this, SLOT(clearAllObjects()));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "closeEvent()";
    event->accept();

    // Otherwise...
    // event->ignore();
}

void MainWindow::clearAllObjects() {
    qDebug() << "Refresh button has been pressed.";
    canvas->clearShapes();
    canvas->update();
}
