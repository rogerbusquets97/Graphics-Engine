#include "submesh.h"
#include "mainwindow.h"
#include "myopenglwidget.h"
extern QOpenGLFunctions_3_3_Core* gl;

SubMesh::SubMesh()
{

}

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size)
    : vertexFormat(vertexFormat), data((unsigned char*)data), data_size(size)
{

}

SubMesh::SubMesh(VertexFormat vert_form, void* d, size_t d_size, uint* ind, uint num_ind) :
                             vertexFormat(vert_form), data_size(d_size), indices_count(num_ind),
                             ibo(QOpenGLBuffer::Type::IndexBuffer)
{
    data = new byte[d_size];
    memcpy(data, d, d_size);
    indices = new unsigned int[num_ind];
    memcpy(indices, ind, num_ind * sizeof(unsigned int));
}

SubMesh::~SubMesh()
{

}

void SubMesh::update()
{
    //VAO: Vertex foormat description and state of VBOs
    vao.create();
    vao.bind();

    //VBO: Buffer with vertex data
    if(data != nullptr)
    {
        vbo.create();
        vbo.bind();
        vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        vbo.allocate(data, int(data_size));
        delete[] data;
        data = nullptr;
    }

    else
    {
        return;
    }

    //IBO: Buffer with indexes
    if (indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indices_count * sizeof(unsigned int)));
        delete[] indices;
        indices = nullptr;
    }

    //Vertex Attributes
    for (int location = 0; location <MAX_VERTEX_ATTRIBUTES; ++location)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];

        if(attr.enabled)
        {
            gl->glEnableVertexAttribArray(GLuint(location));
            gl->glVertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void *)(attr.offset));

        }
    }

    //Release
    vao.release();
    vbo.release();
    if(ibo.isCreated())
    {
        ibo.release();
    }

}

void SubMesh::draw()
{
    int num_vertices = data_size / vertexFormat.size;
    vao.bind();

    if(indices_count > 0)
    {
        gl->glDrawElements(GL_TRIANGLES, int(indices_count), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        gl->glDrawArrays(GL_TRIANGLES, 0, int(num_vertices));
    }

    vao.release();
}

void SubMesh::destroy()
{
    if(vbo.isCreated()) {vbo.destroy(); }
    if(ibo.isCreated()) {ibo.destroy(); }
    if(vao.isCreated()) {vao.destroy(); }
}

