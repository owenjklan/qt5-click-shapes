#include <QApplication>
#include <QPushButton>

#include "ClickShapeWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ClickShapeWidget csw;
    csw.show();
    return QApplication::exec();
}
