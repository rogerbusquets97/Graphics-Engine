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

#include "mesh.h"

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
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void showInfo();

    // Meshes //
    Mesh* CreateMesh();
    void UpdateMeshes();
    void DrawMeshes();
    void CleanUpMeshes();

    Mesh* initializeTriangle();
    void initializeSphere();
    void initializeCube();
    void initialize3DModel(const char* filename);

    void UseShader();

    void EnableVertexAttribArray(GLuint index);
    void VertexAttribPointer(GLuint index,
                             GLint size,
                             GLenum type,
                             GLboolean normalized,
                             GLsizei stride,
                             const GLvoid * pointer);

    /*void keyPressedEvent(QKeyEvent* event);
    void keyReleasedEvent(QKeyEvent* event);
    void mousePressedEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);*/

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
    QOpenGLTexture* Diffuse;
    QOpenGLTexture* NormalMap;

    GLuint normal;
    GLuint diffuse;

    std::list<Mesh*> meshes;

    QTimer timer;

};

extern QOpenGLFunctions_3_3_Core* gl;

#endif // MYOPENGLWIDGET_H
