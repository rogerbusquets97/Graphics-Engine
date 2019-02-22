#include "myopenglwidget.h"

#pragma comment( lib, "OPenGL32.lib" )

myopenglwidget::myopenglwidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void myopenglwidget::initializeGL()
{

}
void myopenglwidget::resizeGL(int w, int h)
{

}
void myopenglwidget::paintGL()
{
    glClearColor(0.8f, 0.2f, 0.9, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
