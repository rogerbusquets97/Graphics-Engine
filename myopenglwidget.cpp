#include "myopenglwidget.h"

#pragma comment( lib, "OPenGL32.lib" )
#include <iostream>
#include "mesh.h"
#include "mainwindow.h"
#include "meshcomponent.h"
#include "scene.h"

extern QOpenGLFunctions_3_3_Core* gl = nullptr;

myopenglwidget::myopenglwidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
}

myopenglwidget::~myopenglwidget()
{
    scene = nullptr;
    makeCurrent();
    FinalizeGL();
}
void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(FinalizeGL));
    gl = this;
    /*program.create();
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
    program.release();*/

    Mesh* patrick = new Mesh();
    patrick->loadModel(":/Models/Patrick/Patrick.obj");

    GameObject* patrick_obj = new GameObject();
    patrick_obj->SetName("Patricio Huguet");

    w->GetCurrScene()->OnAddObject(patrick_obj);

    MeshComponent* mesh = new MeshComponent(patrick, patrick_obj,ComponentType::mesh);

    patrick_obj->OnAddComponent(mesh);
}
void myopenglwidget::resizeGL(int w, int h)
{
    //Resize textures
}
void myopenglwidget::paintGL()
{
    glClearColor(0.8f, 0.2f, 0.9, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(scene!=nullptr)
    {
        scene->Update();
        std::cout << "Paint Scene Objects" << std::endl;
        /*if(program.bind())
        {
            vao.bind();
            glDrawArrays(GL_TRIANGLES,0,3);
            vao.release();
            program.release();
        }*/

    }
    else
    {
        std::cout << "Scene is nullptr" << std::endl;
    }
}

void myopenglwidget::FinalizeGL()
{
    std::cout << "Finalize GL" << std::endl;
}
