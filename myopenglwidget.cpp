#include "myopenglwidget.h"

#pragma comment( lib, "OPenGL32.lib" )
#include <iostream>
#include "mesh.h"
#include "mainwindow.h"
#include "meshcomponent.h"
#include "scene.h"
#include <QOpenGLFramebufferObject>

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

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag.frag");
    program.link();

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
void myopenglwidget::UseShader()
{
    program.bind();
    QMatrix4x4 projectionMatrix;
    const float fovy = 60.0f;
    const float aspectRatio = (float)width()/(float)height();
    const float znear = 0.1;
    const float zfar = 0.1;
    projectionMatrix.perspective(fovy,aspectRatio,znear,zfar);

    QMatrix4x4 viewMatrix;
    QVector3D eyePosition(0.0,1.0,3.0);
    QVector3D center(0.0,0.0,0.0);
    QVector3D up(0.0,1.0,0.0);
    viewMatrix.lookAt(eyePosition,center,up);

    QMatrix4x4 worldMatrix;
    QMatrix4x4 worldViewMatrix = viewMatrix * worldMatrix;

    program.setUniformValue("projectionMatrix", projectionMatrix);
    program.setUniformValue("worldViewMatrix", worldViewMatrix);
}
void myopenglwidget::paintGL()
{
    glClearDepth(1.0f);
    glClearColor(0.4f, 0.4f, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    if(scene!=nullptr)
    {
        UseShader();
        scene->Update();
        QOpenGLFramebufferObject::bindDefault();

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
