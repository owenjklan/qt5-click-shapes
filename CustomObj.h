//
// Created by owen on 19/10/21.
//

#ifndef QT5_CLICK_SHAPES_CUSTOMOBJ_H
#define QT5_CLICK_SHAPES_CUSTOMOBJ_H


#include <QString>
#include <QRect>
#include <QPainter>

class CustomObj {
public:
    CustomObj(QString name, QRect *bounds, QString imageFilename);

    void draw(QPainter *painter);
    void drawCaptionText(QPainter *painter);

    bool selected;
    QString *name;
    QRect *rect;
private:
    QPixmap pixmap;
};


#endif //QT5_CLICK_SHAPES_CUSTOMOBJ_H
