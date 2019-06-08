#include "submesh.h"
#include "mainwindow.h"
#include "myopenglwidget.h"
extern QOpenGLFunctions_3_3_Core* gl;

SubMesh::SubMesh()
{

}

SubMesh::SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->ind = indices;
}

SubMesh::~SubMesh()
{

}

void SubMesh::update()
{
    gl->glGenVertexArrays(1, &VAO);
    gl->glGenBuffers(1, &VBO);
    gl->glGenBuffers(1, &EBO);

    gl->glBindVertexArray(VAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(unsigned int), &ind[0], GL_STATIC_DRAW);

    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    gl->glEnableVertexAttribArray(2);
    gl->glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    gl->glEnableVertexAttribArray(3);
    gl->glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    gl->glEnableVertexAttribArray(4);
    gl->glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    gl->glBindVertexArray(0);
}

void SubMesh::draw()
{

    gl->glBindVertexArray(VAO);

    if(ind.size() > 0)
    {
        gl->glDrawElements(GL_TRIANGLES, int(ind.size()), GL_UNSIGNED_INT, 0);
    }
}

void SubMesh::destroy()
{

}

