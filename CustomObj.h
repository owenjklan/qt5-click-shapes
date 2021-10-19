//
// Created by owen on 19/10/21.
//

#ifndef QT5_CLICK_SHAPES_CUSTOMOBJ_H
#define QT5_CLICK_SHAPES_CUSTOMOBJ_H


#include <QString>
#include <QRect>

class CustomObj {
public:
    CustomObj(QString *name, QRect *bounds);
    bool selected;
    QString *name;
    QRect *rect;
};


#endif //QT5_CLICK_SHAPES_CUSTOMOBJ_H
