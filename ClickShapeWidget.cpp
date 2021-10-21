//
// Created by owen on 13/10/21.
//

#include <QDebug>
#include <QWidget>
#include <QPainter>
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
    painter = new QPainter(this);
    setMinimumWidth(640);
    setMinimumHeight(480);
}

// Points list manipulations
void ClickShapeWidget::addShape(QPoint at) {
    QRect *objBounds = new QRect(at.x(), at.y(), newWidth, newHeight);
    CustomObj *newObj = new CustomObj(currentName, objBounds);
    placements.append(newObj);
}

void ClickShapeWidget::setCurrentName(QString newName) {
    currentName = newName;
}

void ClickShapeWidget::clearShapes() {
    CustomObj *currentObj;

    foreach(currentObj, placements) {
        placements.removeOne(currentObj);
        delete currentObj;
    }
    qDebug() << "All objects cleared.";
}
// END OF Points list manipulations

void ClickShapeWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    painter.setBrush(Qt::SolidPattern);

    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->draw(&painter);
    }

    if (placeMode == true) {
        QRect *rect = new QRect(placeCursorPos.x(), placeCursorPos.y(), newWidth, newHeight);
        CustomObj cursorObject(currentName, rect);
//        painter.setBrush(Qt::SolidPattern);
        cursorObject.draw(&painter);
        update();
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
    placeCursorPos.setX(event->x());
    placeCursorPos.setY(event->y());
    qDebug() << placeCursorPos;
}

void ClickShapeWidget::mouseReleaseEvent(QMouseEvent *event) {
    QString outputStr = QString("%1,%2").arg(event->x()).arg(event->y());

    switch (event->button()) {
        case Qt::LeftButton: {
            if (selectMode == true) {
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

int ClickShapeWidget::redoCount() {
    return redoList.size();
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

// public slots
void ClickShapeWidget::selectAll(bool checked) {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->selected = true;
    }
    update();
}

void ClickShapeWidget::unselectAll(bool checked) {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->selected = false;
    }
    update();
}

void ClickShapeWidget::invertSelection(bool checked) {
    CustomObj *currentObj;
    foreach(currentObj, placements) {
        currentObj->selected = !currentObj->selected;
    }
    update();
}

#define MAX_REDOS       32
void ClickShapeWidget::popPlacement(bool checked) {
    if (placements.length() > 0) {
        CustomObj *backObject = placements.takeLast();
        redoList.push(backObject);
        if (redoList.size() > MAX_REDOS) {
            qDebug() << "Dropping redo, too many in list";
            CustomObj *deletedObject = redoList.takeFirst();
            delete deletedObject;
        }
        qDebug() << "popPlacement():: redoList.size(): " << redoList.size();

        update();
    }
}

void ClickShapeWidget::addPlacementFromRedoList(bool checked) {
    if (redoList.size() == 0) {
        return;
    }

    CustomObj *redoObject = redoList.takeLast();
    qDebug() << "addPlacementFromRedoList():: redoList.size(): " << redoList.size();
    placements.append(redoObject);
    update();
}

void ClickShapeWidget::enableConnectMode() {
    placeMode = false;
    selectMode = true;
    setMouseTracking(false);
    qDebug() << "Connect mode enabeld";
}

void ClickShapeWidget::enablePlaceMode() {
    placeMode = true;
    selectMode = false;
    setMouseTracking(true);
    qDebug() << "Place mode enabled";
}