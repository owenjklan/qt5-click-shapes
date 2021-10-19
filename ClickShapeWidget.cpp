//
// Created by owen on 13/10/21.
//

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "ClickShapeWidget.h"

ClickShapeWidget::ClickShapeWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(640);
    setMinimumHeight(480);
    setStyleSheet("color: #BEB69F;");
}

// Points list manipulations
void ClickShapeWidget::addShape(QPoint at) {
    QRect *newRect = new QRect(at.x(), at.y(), newWidth, newHeight);
    placements.append(newRect);
    update();
}
// END OF Points list manipulations

void ClickShapeWidget::paintEvent(QPaintEvent *event) {
    qDebug() << "paintEvent()";

    QPainter painter(this);
    painter.setBrush(Qt::SolidPattern);
    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(1);

    painter.setPen(pen);

    QRect *newRect;
    foreach(newRect, placements) {
        painter.drawRect(*newRect);
    }
}

void ClickShapeWidget::mousePressEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

//    qDebug() << RED << "(Global) Clicked at:" << NORMAL << event->globalX() << "," << event->globalY();
//    qDebug() << RED << "(Local)  Clicked at:" << NORMAL << event->x() << "," << event->y();

    switch (event->button()) {
        case Qt::LeftButton: {
//            qDebug() << " Left Down @ " << outputStr;
            break;
        }
        case Qt::MidButton: {
//            qDebug() << "  Mid Down @ " << outputStr;
            break;
        }
        case Qt::RightButton: {
//            qDebug() << "Right Down @ " << outputStr;
            break;
        }
        case Qt::XButton1: {
//            qDebug() << "   X1 Down @ " << outputStr;
            break;
        }
        case Qt::XButton2: {
//            qDebug() << "   X2 Down @ " << outputStr;
            break;
        }
        default: {
//            qDebug() << "Unknown Button!" << outputStr;
        }
    }
}

void ClickShapeWidget::mouseMoveEvent(QMouseEvent *event) {

}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

    switch (event->button()) {
        case Qt::LeftButton: {
            qDebug() << "Adding point  @ " << outputStr;
            addShape(QPoint(event->x(), event->y()));
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
            decreaseNewSize();
            break;
        }
        case Qt::XButton2: {
            increaseNewSize();
            break;
        }
        default: {
            qDebug() << "Unknown Button!";
        }
    }
}

void ClickShapeWidget::increaseNewSize() {
    qint32 _width = newWidth << 1;
    qint32 _height = newHeight << 1;
    if (_width > MAX_RECT_WIDTH) {
        newWidth = MAX_RECT_WIDTH;
    } else {
        newWidth = _width;
    }

    if (_height > MAX_RECT_HEIGHT) {
        newHeight = MAX_RECT_HEIGHT;
    } else {
        newHeight = _height;
    }
    QString updateMessage = QString("intial rect. dimensions changed:   %1, %2").arg(newWidth).arg(newHeight);
    qDebug() << updateMessage;
}

void ClickShapeWidget::decreaseNewSize() {
    qint32 _width = newWidth >> 1;
    qint32 _height = newHeight >> 1;
    if (_width < MIN_RECT_WIDTH) {
        newWidth = MIN_RECT_WIDTH;
    } else {
        newWidth = _width;
    }

    if (_height < MIN_RECT_HEIGHT) {
        newHeight = MIN_RECT_HEIGHT;
    } else {
        newHeight = _height;
    }
    QString updateMessage = QString("intial rect. dimensions changed:   %1, %2").arg(newWidth).arg(newHeight);
    qDebug() << updateMessage;
}