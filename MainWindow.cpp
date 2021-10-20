// Created by owen on 19/10/21.

#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QVBoxLayout>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "MainWindow.h"
#include "ClickShapeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    //  UI and Signals must come before Menus and Actions!
    setupUiAndSignals(parent);
    setupMenusAndActions();

    // Load definitions from JSON
    // "object" definitions
    loadObjectDefinitionsJSON();
    populateObjectSelector();
    // Load stylesheet
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

    menuBar()->addSeparator();
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

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
    connectModeButton = new QPushButton("C&onnect");
    connectModeButton->setObjectName("connectModeButton");
    connectModeButton->setToolTip("Change to 'Connect' mode");
    connectModeButton->setToolTipDuration(2000);
    connectModeButton->setCheckable(true);
    connectModeButton->setChecked(false);
    connectModeButton->setMaximumWidth(75);

    placeModeButton = new QPushButton("&Place");
    placeModeButton->setObjectName("placeModeButton");
    placeModeButton->setToolTip("Change to 'Place' mode");
    placeModeButton->setToolTipDuration(2000);
    placeModeButton->setCheckable(true);
    placeModeButton->setChecked(true);
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

void MainWindow::setupObjectSelectGroup(QWidget *parent = nullptr) {
    objectSelectGroup = new QGroupBox(tr("Object Select"));
    objectSelectorCombo = new QComboBox(parent);
    objectSelectorCombo->setMinimumWidth(150);
    objectSelectorCombo->setMaximumWidth(250);

    QHBoxLayout *objSelectLayout = new QHBoxLayout();
    objSelectLayout->addWidget(objectSelectorCombo);
    objectSelectGroup->setLayout(objSelectLayout);

    connect(objectSelectorCombo, SIGNAL(currentTextChanged(const QString &)),
            canvas, SLOT(setCurrentName(QString)));
}

void MainWindow::setupUiAndSignals(QWidget *parent) {
    containerWidget = new QWidget(parent);
    clearButton = new QPushButton("&Clear");
    clearButton->setMaximumWidth(150);
    canvas = new ClickShapeWidget(parent);

    setupModeSelectGroup();
    setupObjectSelectGroup();

    QVBoxLayout *vertLayout = new QVBoxLayout();
    QHBoxLayout *menuHLayout = new QHBoxLayout();

    menuHLayout->addWidget(clearButton);
    menuHLayout->addStretch();
    menuHLayout->addWidget(objectSelectGroup );
    menuHLayout->addWidget(modeSelectGroup);
    vertLayout->addLayout(menuHLayout);
    vertLayout->addWidget(canvas);
    containerWidget->setLayout(vertLayout);
    setCentralWidget(containerWidget);
    setWindowTitle("Qt5 Click Shapes");

    connect(clearButton, SIGNAL(released()),
            this, SLOT(clearAllObjects()));
}

void MainWindow::populateObjectSelector() {
    QString newName;
    foreach(newName, objectNames) {
        objectSelectorCombo->addItem(newName);
    }
}

void MainWindow::loadObjectDefinitionsJSON() {
    QFile inputJsonFile("../objects.json");
    inputJsonFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inputJsonFile.readAll();
    inputJsonFile.close();

    QJsonParseError errorPtr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &errorPtr);
    if (jsonDoc.isNull()) {
        qDebug() << "JSON Parse failed!";
    }
    QJsonObject jsonRootObj = jsonDoc.object();
    QVector<CustomObj> objectDefs;
    QJsonArray objsArray = jsonRootObj.value("objects").toArray();
    qDebug() << objsArray.size() << " object definitions loaded";
    foreach(const QJsonValue &val, objsArray) {
        objectNames.append(val.toObject().value("name").toString());
    }
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