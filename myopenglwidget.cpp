#include "myopenglwidget.h"
#include "vertex.h"
#include "submesh.h"
#include "mesh.h"

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
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag.frag");
    program.link();

    diffuse = glGetUniformLocation(program.programId(), "Albedo");
    normal = glGetUniformLocation(program.programId(), "NormalMap");
    initialize3DModel(":/Models/StoneFloor/StoneFloor.obj");

}

void myopenglwidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
              << debugMessage.message().toStdString() << std::endl;
}

void myopenglwidget::resizeGL(int width, int height)
{
    this->resize(width, height);
}

void myopenglwidget::paintGL()
{
    //gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    UpdateMeshes();

    //w->camera->prepareMatrices();

    glClearDepth(1.0f);
    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    UseShader();
    DrawMeshes();

    QOpenGLFramebufferObject::bindDefault();

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

Mesh* myopenglwidget::CreateMesh()
{
    Mesh* newMesh = new Mesh();
    meshes.push_back(newMesh);
    return newMesh;
}

void myopenglwidget::UpdateMeshes()
{
    for (std::list<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
         if((*it)->needsUpdate)
         {
             (*it)->update();
             (*it)->needsUpdate = false;
         }
    }
}

void myopenglwidget::DrawMeshes()
{
    for (std::list<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        (*it)->draw();
    }
}

void myopenglwidget::UseShader()
{
    if(program.bind())
    {
        camera->PrepareMatrices();
        // Projection transformation
        /*QMatrix4x4 projectionMatrix;
        const float fovy = 60.0f;
        const float aspectRatio = (float)width() / (float)height();
        const float znear = 0.1;
        const float zfar = 1000.0;
        projectionMatrix.perspective(fovy, aspectRatio, znear, zfar);
*/
        // Camera transformation
        QVector3D eyePosition(5.0, 5.0, 10.0);
        QVector3D center(0.0, 0.0, 0.0);
        QVector3D up(0.0, 1.0, 0.0);
        camera->viewMatrix.lookAt(eyePosition, center, up);

        // Object transformation

        QMatrix4x4 worldMatrix;
        QMatrix4x4 worldViewMatrix = camera->viewMatrix * worldMatrix;
        program.setUniformValue("projectionMatrix", camera->projectionMatrix);
        program.setUniformValue("worldViewMatrix", worldViewMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Diffuse->textureId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, NormalMap->textureId());

        glUniform1i(diffuse, 0);
        glUniform1i(normal, 1);
    }
}



void myopenglwidget::initializeCube()
{
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f),
        QVector3D(-0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, -0.5f, 0.0f)
    };
    unsigned int indices[] = {
        0, 2, 1,
        0, 3, 2
    };

    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0, 0, 3);

    Mesh *mesh = this->CreateMesh();
    //mesh->name = "Cube";
    mesh->addSubMesh(vertexFormat, vertices, sizeof(vertices), indices, sizeof(indices));
    mesh->needsUpdate = true;
}

Mesh* myopenglwidget::initializeTriangle()
{
    //Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader1.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader1.frag");
    program.link();
    program.bind();

    //VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), //Vertex 1
        QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), //Vertex 2
        QVector3D( 0.0f,  0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)  //Vertex 3
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));

    //VAO: Captures state of VBOs
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    vao.release();
    program.release();
    vbo.release();

    return nullptr;
}

void myopenglwidget::initializeSphere()
{

    Vertex sphere[H][V + 1];
    for(int i = 0; i < H; ++i)
    {
        for(int j = 0; j < V + 1; ++j)
        {
            float nh = float(i) / H;
            float nv = float(j) / V - 0.5f;
            float angleh = 2 * pi * nh;
            float anglev = -pi * nv;

            sphere[i][j].pos.setX(sinf(angleh) * cosf(anglev));
            sphere[i][j].pos.setY(-sinf(anglev));
            sphere[i][j].pos.setZ(cosf(angleh) * cosf(anglev));
            sphere[i][j].norm = sphere[i][j].pos;
        }
    }

    unsigned int sphereIndices[H][V][6];

    for (unsigned int i = 0; i < H; ++i)
    {
        for (unsigned int j = 0; j < V + 1; ++j)
        {
            sphereIndices[i][j][0] = (i+0)      * (V+1) + j;
            sphereIndices[i][j][1] = ((i+1)%H)  * (V+1) + j;
            sphereIndices[i][j][2] = ((i+1)%H)  * (V+1) + j+1;
            sphereIndices[i][j][3] = (i+0)      * (V+1) + j;
            sphereIndices[i][j][4] = ((i+1)%H)  * (V+1) + j+1;
            sphereIndices[i][j][5] = (i+0)      * (V+1) + j+1;
        }
    }

    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0,0,3);
    vertexFormat.setVertexAttribute(1, sizeof(QVector3D), 3);

    Mesh *mesh = this->CreateMesh();
    //mesh->name = "Sphere";
    mesh->addSubMesh(vertexFormat, sphere, sizeof(sphere), &sphereIndices[0][0][0], H*V*6);
    mesh->needsUpdate = true;
}

void myopenglwidget::initialize3DModel(const char* filename)
{
    Mesh *mesh = this->CreateMesh();
    //mesh->name = filename;
    mesh->loadModel(filename);
    QImage diffuse;
    diffuse.load(":/Models/StoneFloor/diffuse.png");
    Diffuse = new QOpenGLTexture(diffuse.mirrored());
    Diffuse->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    Diffuse->setMagnificationFilter(QOpenGLTexture::Linear);

    QImage normalmap;
    normalmap.load(":/Models/StoneFloor/n.png");
    NormalMap = new QOpenGLTexture(normalmap.mirrored());
    NormalMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    NormalMap->setMagnificationFilter(QOpenGLTexture::Linear);
}

void myopenglwidget::CleanUpMeshes()
{
    for (std::list<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        if((*it) != nullptr)
            delete (*it);
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
