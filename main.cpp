#include <QApplication>
#include <QPushButton>

#include "MainWindow.h"
#include "ClickShapeWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    //    ClickShapeWidget csw;
    //    csw.show();
    return QApplication::exec();
}
