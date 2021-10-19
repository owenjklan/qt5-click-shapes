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

void ClickShapeWidget::setupPainter() {
    qDebug() << "setupPainter()";
}

void ClickShapeWidget::paintShapes() {
    qDebug() << "paintShapes()";
}

void ClickShapeWidget::setupUiAndSignals(QWidget *parent) {
    button = new QPushButton("Press me!");
    canvas = new QWidget();
    canvas->setMinimumWidth(640);
    canvas->setMinimumHeight(480);

    canvas->setStyleSheet("background-color: #BEB69F;");

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(button);
    layout->addWidget(canvas);

    setLayout(layout);
    setWindowTitle("Qt5 Click Shapes");
}

#define RED "\033[33;1m"
#define NORMAL "\033[0m"

void ClickShapeWidget::mousePressEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

//    qDebug() << RED << "(Global) Clicked at:" << NORMAL << event->globalX() << "," << event->globalY();
//    qDebug() << RED << "(Local)  Clicked at:" << NORMAL << event->x() << "," << event->y();

    switch (event->button()) {
        case Qt::LeftButton: {
            qDebug() << " Left Down @ " << outputStr;
            break;
        }
        case Qt::MidButton: {
            qDebug() << "  Mid Down @ " << outputStr;
            break;
        }
        case Qt::RightButton: {
            qDebug() << "Right Down @ " << outputStr;
            break;
        }
        case Qt::XButton1: {
            qDebug() << "   X1 Down @ " << outputStr;
            break;
        }
        case Qt::XButton2: {
            qDebug() << "   X2 Down @ " << outputStr;
            break;
        }
        default: {
            qDebug() << "Unknown button!" << outputStr;
        }
    }
}

void ClickShapeWidget::mouseMoveEvent(QMouseEvent *event) {

}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

    switch (event->button()) {
        case Qt::LeftButton: {
            qDebug() << " Left Up   @ " << outputStr;
            break;
        }
        case Qt::MidButton: {
            qDebug() << "  Mid Up   @ " << outputStr;
            break;
        }
        case Qt::RightButton: {
            qDebug() << "Right Up   @ " << outputStr;
            break;
        }
        case Qt::XButton1: {
            qDebug() << "   X1 Up   @ " << outputStr;
            break;
        }
        case Qt::XButton2: {
            qDebug() << "   X2 Up   @ " << outputStr;
            break;
        }
        default: {
            qDebug() << "Unknown button!";
        }
    }
}

void ClickShapeWidget::addShape(QPoint at) {
    placements.append(at);
}