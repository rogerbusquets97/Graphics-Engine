#ifndef SUBMESH_H
#define SUBMESH_H

#include "vertex.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <vector>

class SubMesh :
        protected QOpenGLFunctions_3_3_Core
{
public:
    SubMesh();
    SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~SubMesh();

    void update();
    void draw();
    void destroy();

private:

    std::vector<Vertex>vertices;
    std::vector<unsigned int> ind;

    unsigned int VAO, VBO, EBO;

};

#endif // SUBMESH_H
