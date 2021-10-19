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

    removeLastPlacedAction = new QAction(tr("&Undo Placement"));
    removeLastPlacedAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));

    redoPlacementAction = new QAction(tr("&Redo Placement"));
    redoPlacementAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z));
    redoPlacementAction->setText(QString("&Redo Placement (%1)").arg(canvas->redoCount()));

    fileMenu = menuBar()->addMenu(tr("&File"));

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(removeLastPlacedAction);
    editMenu->addAction(redoPlacementAction);

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
//    connect(removeLastPlacedAction, SIGNAL(triggered(bool)),
//            canvas, SLOT(popPlacement(bool)));
//    connect(redoPlacementAction, SIGNAL(triggered(bool)),
//            canvas, SLOT(addPlacementFromRedoList(bool)));
    connect(removeLastPlacedAction, SIGNAL(triggered(bool)),
            this, SLOT(undoPlacement(bool)));
    connect(redoPlacementAction, SIGNAL(triggered(bool)),
            this, SLOT(redoPlacement(bool)));
}

void MainWindow::setupModeSelectGroup() {
    modeSelectGroup = new QGroupBox(tr("Mode Select"));
    modeSelectGroup->setCheckable(true);
    connectModeButton = new QPushButton("Connect");
    connectModeButton->setToolTip("Change to 'Connect' mode");
    connectModeButton->setToolTipDuration(2000);
    connectModeButton->setCheckable(true);
    connectModeButton->setChecked(true);
    connectModeButton->setMaximumWidth(75);

    placeModeButton = new QPushButton("Place");
    placeModeButton->setToolTip("Change to 'Place' mode");
    placeModeButton->setToolTipDuration(2000);
    placeModeButton->setCheckable(true);
    placeModeButton->setChecked(false);
    placeModeButton->setMaximumWidth(75);

    QHBoxLayout *modeButtonsLayout = new QHBoxLayout();
    modeButtonsLayout->addWidget(connectModeButton);
    modeButtonsLayout->addWidget(placeModeButton);
    modeSelectGroup->setLayout(modeButtonsLayout);

    connect(connectModeButton, SIGNAL(toggled(bool)),
            this, SLOT(connectModeChecked(bool)));
    connect(placeModeButton, SIGNAL(toggled(bool)),
            this, SLOT(placeModeChecked(bool)));
}

void MainWindow::setupUiAndSignals(QWidget *parent) {
    containerWidget = new QWidget(parent);
    clearButton = new QPushButton("&Clear");
    clearButton->setMaximumWidth(150);
    canvas = new ClickShapeWidget(parent);

    setupModeSelectGroup();

    QVBoxLayout *vertLayout = new QVBoxLayout();
    QHBoxLayout *menuHLayout = new QHBoxLayout();

    menuHLayout->addWidget(clearButton);
    menuHLayout->addStretch();
    menuHLayout->addWidget(modeSelectGroup);
    vertLayout->addLayout(menuHLayout);
    vertLayout->addWidget(canvas);
    containerWidget->setLayout(vertLayout);
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

void MainWindow::undoPlacement(bool checked) {
    qDebug() << "Updating 'redo count in menus...";
    canvas->popPlacement(checked);
    qDebug() << "MainWindow::undoPlacement(): canvas->redoCount(): " << canvas->redoCount();
    redoPlacementAction->setText(QString("&Redo Placement (%1)").arg(canvas->redoCount()));
    canvas->update();
    editMenu->update();
}

void MainWindow::redoPlacement(bool checked) {
    qDebug() << "Updating 'redo count' in menus...";
    canvas->addPlacementFromRedoList(checked);
    qDebug() << "MainWindow::redoPlacement(): canvas->redoCount(): " << canvas->redoCount();
    redoPlacementAction->setText(QString("&Redo Placement (%1)").arg(canvas->redoCount()));
    canvas->update();
    editMenu->update();
}

void MainWindow::connectModeChecked(bool checked) {
//    qDebug() << "connectModeChecked(checked=" << checked << ")";
    placeModeButton->setChecked(!checked);
    if (checked == true) {
        canvas->enableConnectMode();
    }
}

void MainWindow::placeModeChecked(bool checked) {
//    qDebug() << "placeModeChecked(checked=" << checked << ")";
    connectModeButton->setChecked(!checked);
    if (checked == true) {
        canvas->enablePlaceMode();
    }
}