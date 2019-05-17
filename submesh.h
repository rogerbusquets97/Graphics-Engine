#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#define MAX_VERTEX_ATTRIBUTES 4

struct Vertex { QVector3D pos; QVector3D norm; };

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:

    void setVertexAttribute(int location, int offset, int ncomp)
    {
        attribute[location].enabled = true;
        attribute[location].offset = offset;
        attribute[location].ncomp = ncomp;
        size+= ncomp* sizeof(float);
    }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

class SubMesh :
        protected QOpenGLFunctions_3_3_Core
{
public:
    SubMesh();
    SubMesh(VertexFormat vertexFormat, void* d, size_t d_size, uint* indices, uint indices_count);
    ~SubMesh();

    void update();
    void draw();
    void cleanup();

private:
    VertexFormat vertexFormat;
    unsigned char *data = nullptr;
    size_t data_size = 0;
    unsigned int *indices = nullptr;
    size_t indices_count = 0;

    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
};
#endif // SUBMESH_H
