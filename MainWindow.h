// Created by owen on 19/10/21.

#ifndef QT5_CLICK_SHAPES_MAINWINDOW_H
#define QT5_CLICK_SHAPES_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStyle>
#include <QMainWindow>
#include <QGroupBox>
#include <QComboBox>

#include "ClickShapeWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void clearAllObjects();
    void undoPlacement(bool checked = false);
    void redoPlacement(bool checked = false);
    void connectModeChecked(bool checked = true);
    void placeModeChecked(bool checked = true);

private:
    void setupUiAndSignals(QWidget *parent);
    void setupMenusAndActions();
    void setupModeSelectGroup();
    void setupObjectSelectGroup(QWidget *parent);
    void populateObjectSelector();
    void loadObjectDefinitionsJSON();

    QWidget *containerWidget;
    QPushButton *clearButton;
    ClickShapeWidget *canvas;

    QGroupBox *modeSelectGroup;
    QPushButton *placeModeButton;
    QPushButton *connectModeButton;

    QGroupBox *objectSelectGroup;
    QComboBox *objectSelectorCombo;

    QVector<QString> objectNames;

    // Menu objects
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectMenu;

    // Menu actions
    QAction *removeLastPlacedAction;
    QAction *redoPlacementAction;
    QAction *selectAllAction;
    QAction *unselectAllAction;
    QAction *invertSelectionAction;

};
#endif //QT5_CLICK_SHAPES_MAINWINDOW_H
