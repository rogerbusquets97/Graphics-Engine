#include "mainwindow.h"
#include <QApplication>

MainWindow* w = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow();
    w->show();

    //When app exits delete w
    return a.exec();
}
