//
// Created by owen on 13/10/21.
//

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QShortcut>
#include <QKeySequence>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QApplication>
#include <QStyleOption>

#include "ClickShapeWidget.h"
#include "CustomObj.h"

ClickShapeWidget::ClickShapeWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(640);
    setMinimumHeight(480);

    selectAllShortcut = new QShortcut(
            QKeySequence(Qt::CTRL + Qt::Key_A),
            this
    );
    unselectAllShortcut = new QShortcut(
            QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A),
            this
    );

    connect(selectAllShortcut, SIGNAL(activated()),
            this, SLOT(selectAll()));
    connect(unselectAllShortcut, SIGNAL(activated()),
            this, SLOT(unselectAll()));
}

// Points list manipulations
void ClickShapeWidget::addShape(QPoint at) {
    QRect *objBounds = new QRect(at.x(), at.y(), newWidth, newHeight);
    CustomObj *newObj = new CustomObj(new QString("Foobar"), objBounds);
    placements.append(newObj);
}
// END OF Points list manipulations

void ClickShapeWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setBrush(Qt::SolidPattern);
    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(1);

    painter.setPen(pen);

    CustomObj *currentObj;
    foreach(currentObj, placements) {
        if (currentObj->selected) {
            pen.setColor(Qt::red);
            pen.setWidth(2);
        } else {
            pen.setColor(Qt::green);
            pen.setWidth(1);
        }
        painter.setPen(pen);
        painter.drawRect(*currentObj->rect);
    }
}

void ClickShapeWidget::mousePressEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

    switch (event->button()) {
        case Qt::LeftButton: {
            break;
        }
        case Qt::MidButton: {
            break;
        }
        case Qt::RightButton: {
            break;
        }
        case Qt::XButton1: {
            break;
        }
        case Qt::XButton2: {
            break;
        }
        default: {
            qDebug() << "Unknown Button!" << outputStr;
        }
    }
}

void ClickShapeWidget::mouseMoveEvent(QMouseEvent *event) {

}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

    switch (event->button()) {
        case Qt::LeftButton: {
            if (QApplication::queryKeyboardModifiers() == Qt::CTRL) {
                CustomObj *selectedObj = findSelectedObj(event->pos());
                if (selectedObj == nullptr) {
                    break;
                }
                QString debugMessage = QString("Selected Rect @ %1, %2 (%3x%4)")\
                .arg(selectedObj->rect->x())\
                .arg(selectedObj->rect->y())\
                .arg(selectedObj->rect->width())\
                .arg(selectedObj->rect->height());
                qDebug() << debugMessage;

            } else { // Add new object
                qDebug() << "Adding point  @ " << outputStr;
                addShape(QPoint(event->x(), event->y()));
            }
            break;
        }
        case Qt::MidButton: {
            qDebug() << "  Mid Up   @ " << outputStr;
            break;
        }
        case Qt::RightButton: {
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
    update();
}

CustomObj * ClickShapeWidget::findSelectedObj(QPoint at) {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        if (currentObj->rect->contains(at)) {
            currentObj->selected = !currentObj->selected;
            return currentObj;
        }
    }
    return nullptr;
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

void ClickShapeWidget::selectAll() {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->selected = true;
    }
    update();
}

void ClickShapeWidget::unselectAll() {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->selected = false;
    }
    update();
}