#include "myopenglwidget.h"

#pragma comment( lib, "OPenGL32.lib" )
#include <iostream>

myopenglwidget::myopenglwidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    FinalizeGL();
}
void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(FinalizeGL));

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shader1_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag.frag");
    program.link();
    program.bind();

    //VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f,-0.5f,0.0f),QVector3D(1.0f,0.0f,0.0f),
        QVector3D(0.5f,-0.5f,0.0f),QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.0f,0.5f,0.0f),QVector3D(0.0f,0.0f,1.0f)
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices,6*sizeof (QVector3D));

    //vao
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2*sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes1));

    //Release
    vao.release();
    vbo.release();
    program.release();
}
void myopenglwidget::resizeGL(int w, int h)
{
    //Resize textures
}
void myopenglwidget::paintGL()
{
    glClearColor(0.8f, 0.2f, 0.9, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES,0,3);
        vao.release();
        program.release();
    }

}

void myopenglwidget::FinalizeGL()
{
    std::cout << "Finalize GL" << std::endl;
}
