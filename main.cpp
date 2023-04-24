
#include "mainwindow.h"
#include "menu.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Menu m;
    m.showMaximized();
    return a.exec();
}
