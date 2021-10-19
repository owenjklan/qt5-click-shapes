//
// Created by owen on 13/10/21.
//

#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
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
}

void ClickShapeWidget::mousePressEvent(QMouseEvent *event) {
    QPointF screenPos = event->screenPos();
    qDebug() << "(Global) Clicked at: " << event->globalX() << "," << event->globalY();
    qDebug() << "(Local)  Clicked at: " << event->x() << "," << event->y();
    qDebug() << "\033[33;1mscreenPos()\033[0m:         " << screenPos.x() << "," << screenPos.y();
}

void ClickShapeWidget::mouseMoveEvent(QMouseEvent *event) {

}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {

}