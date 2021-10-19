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

#define RED "\033[33;1m"
#define NORMAL "\033[0m"

void ClickShapeWidget::mousePressEvent(QMouseEvent *event) {
    QPointF screenPos = event->screenPos();
    qDebug() << RED << "(Global) Clicked at:" << NORMAL << event->globalX() << "," << event->globalY();
    qDebug() << RED << "(Local)  Clicked at:" << NORMAL << event->x() << "," << event->y();
    qDebug() << RED << "screenPos()        :" << NORMAL << screenPos.x() << "," << screenPos.y();

    switch (event->button()) {
        case Qt::LeftButton: {
            qDebug() << "Left Down";
            break;
        }
        case Qt::MidButton: {
            qDebug() << "Mid Down";
            break;
        }
        case Qt::RightButton: {
            qDebug() << "Right Down";
            break;
        }
        case Qt::XButton1: {
            qDebug() << "X1 Down";
            break;
        }
        case Qt::XButton2: {
            qDebug() << "X2 Down";
            break;
        }
        default: {
            qDebug() << "Unknown button!";
        }
    }
}

void ClickShapeWidget::mouseMoveEvent(QMouseEvent *event) {

}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    switch (event->button()) {
        case Qt::LeftButton: {
            qDebug() << "Left Up";
            break;
        }
        case Qt::MidButton: {
            qDebug() << "Mid Up";
            break;
        }
        case Qt::RightButton: {
            qDebug() << "Right Up";
            break;
        }
        case Qt::XButton1: {
            qDebug() << "X1 Up";
            break;
        }
        case Qt::XButton2: {
            qDebug() << "X2 Up";
            break;
        }
        default: {
            qDebug() << "Unknown button!";
        }
    }
}