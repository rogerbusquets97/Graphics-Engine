#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include "scene.h"
#include <QOpenGLDebugLogger>
#include "mesh.h"

class myopenglwidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit myopenglwidget(QWidget *parent = nullptr);
    ~myopenglwidget()override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void UseShader();
    Mesh* CreateMesh();
    void UpdateMeshes();
    void DrawMeshes();

    /*QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;*/
    QOpenGLShaderProgram program;
    Scene* scene;
    QList<Mesh*>meshes;

    void mousePressEvent(QMouseEvent * event);
signals:

public slots:
    void FinalizeGL();
    void handleLoggedMessage(const QOpenGLDebugMessage &debugMessage);
};

#endif // MYOPENGLWIDGET_H
