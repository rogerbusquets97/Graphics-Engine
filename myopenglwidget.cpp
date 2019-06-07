#include "myopenglwidget.h"
#include "vertex.h"
#include "submesh.h"
#include "mesh.h"
#include "scene.h"
#include "meshcomponent.h"

#include <iostream>
#include <QOpenGLDebugLogger>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>

#include "mainwindow.h"

#pragma comment( lib, "OpenGL32.lib" )

QOpenGLFunctions_3_3_Core *gl = nullptr;

myopenglwidget::myopenglwidget(QWidget *parent)
    : QOpenGLWidget (parent)
{
   // setMinimumSize(QSize(256, 256));
    setMouseTracking(true);

    connect(&timer, SIGNAL(timeout()),this,SLOT(Frame()));
    if(format().swapInterval() == -1)
    {
        qDebug("Swap Buffers at v_blank not available: refresh at approx 60fps.");
        timer.setInterval(17);
    }
    else
    {
        qInfo("V_blank synchronization available");
        timer.setInterval(0);
    }

    input = new Input();
    camera = new Camera();

    interaction = new Interaction();
    interaction->input = input;
    interaction->camera = camera;

    timer.start();
}

void myopenglwidget::Frame()
{
    //Update
    bool interacted = interaction->Update();
    if(interacted)
    {
        update();
    }

    input->postUpdate();

}

void myopenglwidget::keyPressEvent(QKeyEvent *event)
{
    input->keyPressedEvent(event);
}

void myopenglwidget::keyReleaseEvent(QKeyEvent *event)
{
    input->keyReleasedEvent(event);
}

void myopenglwidget::mousePressEvent(QMouseEvent *event)
{
    input->mousePressedEvent(event);
}

void myopenglwidget::mouseMoveEvent(QMouseEvent *event)
{
    input->mouseMoveEvent(event);
}

void myopenglwidget::mouseReleaseEvent(QMouseEvent *event)
{
    input->mouseReleaseEvent(event);
}

void myopenglwidget::enterEvent(QEvent *)
{
    grabKeyboard();
}

void myopenglwidget::leaveEvent(QEvent *)
{
    releaseKeyboard();
}

void myopenglwidget::wheelEvent(QWheelEvent* event)
{
    input->mouseWheelEvent(event);
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();
    delete input;
    delete camera;
    delete interaction;
}

void myopenglwidget::InitGBuffer()
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    //Position
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    //Nomal
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    //Color
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);


    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

    glUniform1i(glGetUniformLocation(program.programId(),"gPosition"),0);
    glUniform1i(glGetUniformLocation(program.programId(),"gNormal"),1);
    glUniform1i(glGetUniformLocation(program.programId(),"gAlbedo"),2);

}

void myopenglwidget::initializeGL()
{
    gl = this;
    initializeOpenGLFunctions();

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()),
            this, SLOT(finalizeGL()));

    if(context()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
    {
        QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
        logger->initialize();

        connect(logger, SIGNAL(messageLogged(const QOpenGLDebugMessage &)),
                this, SLOT(handleLoggedMessage(const QOpenGLDebugMessage &)));
        logger->startLogging();
    }

    glEnable(GL_DEPTH_TEST);

    //Shaders
    //Lightning shaders
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/lightning.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/lightning.frag");
    program.link();

   /* diffuse = glGetUniformLocation(program.programId(), "Albedo");
    normal = glGetUniformLocation(program.programId(), "NormalMap");*/

    // Geometry shaders
    geometryProgram.create();
    geometryProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/geometry.vert");
    geometryProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/geometry.frag");
    program.link();

    InitGBuffer();
}

void myopenglwidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
              << debugMessage.message().toStdString() << std::endl;
}

void myopenglwidget::resizeGL(int width, int height)
{
    this->resize(width, height);
    int side = qMin(width, height);
        glViewport((width - side) / 2, (height - side) / 2, side, side);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
    #ifdef QT_OPENGL_ES_1
        glOrthof(-2, +2, -2, +2, 1.0, 15.0);
    #else
        glOrtho(-2, +2, -2, +2, 1.0, 15.0);
    #endif
        glMatrixMode(GL_MODELVIEW);
}

void myopenglwidget::paintGL()
{
    //gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    UpdateMeshes();

    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);

    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UseGeometryShader();
    DrawMeshes();
    QOpenGLFramebufferObject::bindDefault();

    //Use lightning shader
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UseLightningShader();
    //Render quad
    RenderQuad();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0,0, this->width(), this->height(), 0,0,this->width(), this->height(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void myopenglwidget::finalizeGL()
{
    std::cout << "finalize()" << std::endl;
}

void myopenglwidget::showInfo()
{
    std::cout << "OpenGL version:" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL renderer:" << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl << std::endl;

    std::cout << "OpenGL vendor:" << std::endl;
    std::cout << glGetString(GL_VENDOR) << std::endl << std::endl;

    std::cout << "OpenGL GLSL version:" << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL extensions:" << std::endl;
    GLint num_extensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
    for (int i = 0; i < num_extensions; ++i)
    {
        const unsigned char *str = glGetStringi(GL_EXTENSIONS, GLuint(i));
        std::cout << str << " ";
    }
    std::cout << std::endl;

    //Information about the surface format
    std::cout << context()->format().redBufferSize() << std::endl;
    std::cout << context()->format().greenBufferSize() << std::endl;
    std::cout << context()->format().blueBufferSize() << std::endl;
    std::cout << context()->format().alphaBufferSize() << std::endl;
    std::cout << context()->format().depthBufferSize() << std::endl;
}

void myopenglwidget::UpdateMeshes()
{
    QList<Mesh*> Scenemeshes;
    w->GetCurrScene()->GetSceneMeshes(Scenemeshes);
    for(QList<Mesh*>::iterator it = Scenemeshes.begin(); it!= Scenemeshes.end(); ++it)
    {
        if((*it)->needsUpdate)
        {
            (*it)->update();
            (*it)->needsUpdate = false;
        }
    }
}

void myopenglwidget::RenderQuad()
{
    if(quadVAO == 0)
    {
        float quadVertices[] = {
                    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                };

        glGenVertexArrays(1,&quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof (float)));
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
    glBindVertexArray(0);
}
void myopenglwidget::DrawMeshes()
{
    QList<Mesh*> Scenemeshes;
    w->GetCurrScene()->GetSceneMeshes(Scenemeshes);

    for(QList<Mesh*>::iterator it = Scenemeshes.begin(); it!= Scenemeshes.end(); ++it)
    {
        if((*it)->GetMaterial()->GetDiffuse()!= nullptr)
        {
            diffuse = glGetUniformLocation(program.programId(), "diffuseTexture");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*it)->GetMaterial()->GetDiffuse()->textureId());
            glUniform1i(diffuse, 0);
        }
        (*it)->draw();
    }
}

void myopenglwidget::UseGeometryShader()
{
    if(geometryProgram.bind())
    {
        camera->PrepareMatrices();
        // Camera transformation
        QVector3D eyePosition(5.0, 5.0, 10.0);
        QVector3D center(0.0, 0.0, 0.0);
        QVector3D up(0.0, 1.0, 0.0);
        camera->viewMatrix.lookAt(eyePosition, center, up);

        // Object transformation

        QMatrix4x4 worldMatrix;
        QMatrix4x4 worldViewMatrix = camera->viewMatrix * worldMatrix;
        geometryProgram.setUniformValue("projectionMatrix", camera->projectionMatrix);
        geometryProgram.setUniformValue("worldViewMatrix", worldViewMatrix);
    }
}

void myopenglwidget::UseLightningShader()
{
    if(program.bind())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);
    }
}

void myopenglwidget::EnableVertexAttribArray(GLuint index)
{
    glEnableVertexAttribArray(index);
}

void myopenglwidget::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}



