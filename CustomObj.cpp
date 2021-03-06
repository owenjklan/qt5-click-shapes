//
// Created by owen on 19/10/21.
//

#include "CustomObj.h"

CustomObj::CustomObj(QString objName, QRect *objRect, QString imageFilename) {
    selected = false;
    name = new QString(objName);
    rect = new QRect(*objRect);
    pixmap = QPixmap::fromImage(QImage(imageFilename));
}

void CustomObj::draw(QPainter *painter) {
    QPen pen;

    if (selected) {
        pen.setColor(Qt::red);
        pen.setWidth(2);
    } else {
        pen.setColor(Qt::green);
        pen.setWidth(1);
    }
    painter->setPen(pen);
//    painter->drawRect(*rect);
    painter->drawPixmap(*rect, pixmap);
    pen.setColor(Qt::white);
    drawCaptionText(painter);
}

void CustomObj::drawCaptionText(QPainter *painter) {
    int textX, textY;
    QPen pen;
    pen.setColor(Qt::white);
    painter->setPen(pen);
    textX = rect->x() + 1;
    textY = rect->y() + 1;
    QRect textRect(textX, textY, rect->width(), 48);
    painter->drawText(textRect, *name);
}