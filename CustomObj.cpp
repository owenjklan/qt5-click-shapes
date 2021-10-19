//
// Created by owen on 19/10/21.
//

#include "CustomObj.h"

CustomObj::CustomObj(QString *objName, QRect *objRect) {
    selected = false;
    name = objName;
    rect = objRect;
}