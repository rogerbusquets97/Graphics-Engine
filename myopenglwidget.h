#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>
#include <QTimer>
#include <QWheelEvent>

#include "mesh.h"
#include "input.h"
#include "interaction.h"
#include "camera.h"
#include "componentlight.h"

// Sphere //
#define H 32
#define V 16

class myopenglwidget :
        public QOpenGLWidget,
        public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit myopenglwidget(QWidget *parent = nullptr);
    ~myopenglwidget() override;

    //From these methods we can call OpenGL function
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void showInfo();

    // Meshes //
    void UpdateMeshes();
    void DrawMeshes();
    void RenderQuad();

    void ResizeTextures();

    void UseGeometryShader();
    void UseLightningShader();
    void InitGBuffer();
    void EnableVertexAttribArray(GLuint index);
    void VertexAttribPointer(GLuint index,
                             GLint size,
                             GLenum type,
                             GLboolean normalized,
                             GLsizei stride,
                             const GLvoid * pointer);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEvent* )override ;
    void leaveEvent(QEvent*)override;
    void wheelEvent(QWheelEvent* event)override;
    Interaction* interaction;

signals:
    void messageLogged(const QOpenGLDebugMessage &);

public slots:

    //Not virtual
    void finalizeGL();
    void handleLoggedMessage(const QOpenGLDebugMessage &);
    void Frame();

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram geometryProgram;

    GLuint normal;
    GLuint diffuse;

    QTimer timer;
    Input* input;

    Camera* camera;

    //GBuffer
    unsigned int gBuffer;
    unsigned int gPosition;
    unsigned int gNormal;
    unsigned int gAlbedo;

    //Screen Quad
    unsigned int quadVAO = 0;
    unsigned int quadVBO;

    bool diffuseEnabled = true;
    bool normalEnabled = true;
    bool parallaxEnabled = true;
};

extern QOpenGLFunctions_3_3_Core* gl;

#endif // MYOPENGLWIDGET_H
