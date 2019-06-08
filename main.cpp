#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

MainWindow* w = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(0);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);
    w = new MainWindow();
    w->show();

    //When app exits delete w
    if(!w->running)
    {
        delete w;
    }
    return a.exec();
}
