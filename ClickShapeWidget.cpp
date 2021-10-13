//
// Created by owen on 13/10/21.
//

#include <QWidget>
#include <QVBoxLayout>
#include "ClickShapeWidget.h"

ClickShapeWidget::ClickShapeWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUiAndSignals(parent);
}

ClickShapeWidget::~ClickShapeWidget() noexcept {
    ;
}

void ClickShapeWidget::setupUiAndSignals(QWidget *parent) {
    button = new QPushButton("Press me!");
    canvas = new QWidget();
    canvas->setMinimumWidth(640);
    canvas->setMinimumHeight(480);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(button);
    layout->addWidget(canvas);

    setLayout(layout);
    setWindowTitle("Qt5 Click Shapes");

    connect(canvas, SIGNAL(released()), this, SLOT(onCanvasClick()));
}

void ClickShapeWidget::onCanvasClick() {

}