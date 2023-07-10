#include "mainwindow.h"
#include <QApplication>

extern const int TILE_SIZE = 10;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
