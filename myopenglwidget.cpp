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
    gl = this;
    initializeOpenGLFunctions();
    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(FinalizeGL));

    if(context()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
   {
       QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
       logger->initialize();

       connect(logger, SIGNAL(messageLogged(const QOpenGLDebugMessage &)),
               this, SLOT(handleLoggedMessage(const QOpenGLDebugMessage &)));
       logger->startLogging();
   }


    glEnable(GL_DEPTH_TEST);

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag.frag");
    program.link();

    Mesh* patrick = CreateMesh();
    patrick->loadModel(":/Models/Patrick/Patrick.obj");

    /*GameObject* patrick_obj = new GameObject();
    patrick_obj->SetName("Patricio Huguet");
    w->GetCurrScene()->OnAddObject(patrick_obj);
    MeshComponent* mesh = new MeshComponent(patrick, patrick_obj,ComponentType::mesh);
    patrick_obj->OnAddComponent(mesh);*/
}
void myopenglwidget::resizeGL(int w, int h)
{
    //Resize textures
    this->resize(w, h);
}

void myopenglwidget::DrawMeshes()
{
    for (QList<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        (*it)->draw();
    }
}

void myopenglwidget::UpdateMeshes()
{
    for (QList<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        (*it)->update();
    }
}
void myopenglwidget::UseShader()
{
    std::cout << "Use shader" << std::endl;
    if (program.bind())
    {
        QMatrix4x4 projectionMatrix;
        const float fovy = 60.0f;
        const float aspectRatio = (float)width()/(float)height();
        const float znear = 0.1;
        const float zfar = 1000.0;
        projectionMatrix.perspective(fovy,aspectRatio,znear,zfar);

        QMatrix4x4 viewMatrix;
        QVector3D eyePosition(5.0,5.0,10.0);
        QVector3D center(0.0,0.0,0.0);
        QVector3D up(0.0,1.0,0.0);
        viewMatrix.lookAt(eyePosition,center,up);

        QMatrix4x4 worldMatrix;
        QMatrix4x4 worldViewMatrix = viewMatrix * worldMatrix;

        program.setUniformValue("projectionMatrix", projectionMatrix);
        program.setUniformValue("worldViewMatrix", worldViewMatrix);

        program.release();
    }
}

Mesh* myopenglwidget::CreateMesh()
{
    Mesh* m = new Mesh();
    meshes.push_back(m);
    return m;
}
void myopenglwidget::paintGL()
{
    UpdateMeshes();

    glClearDepth(1.0f);
    glClearColor(0.4f, 0.4f, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    UseShader();
    DrawMeshes();
    QOpenGLFramebufferObject::bindDefault();
}

void myopenglwidget::FinalizeGL()
{
    std::cout << "Finalize GL" << std::endl;
}

void  myopenglwidget::mousePressEvent(QMouseEvent * event)
{
    update();
}

void myopenglwidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
                 << debugMessage.message().toStdString() << std::endl;
}
