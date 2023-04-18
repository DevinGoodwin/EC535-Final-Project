
#include "mainwindow.h"
#include "menu.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Menu m;
    m.setGeometry(QRect(0,0,800,600));
    m.show();
    return a.exec();
}
