#include "submesh.h"

#include <iostream>


void SubMesh::update()
{
    // VAO: Vertex format description and stato of VBOs
    vao.create();
    vao.bind();

    //VBO: Buffer with vertex data
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data, int(data_size));
    delete[] data;
    data = nullptr;

    // IBO: Buffer with Indexes
    if (indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indices_count *sizeof (unsigned int)));
        delete[] indices;
        indices = nullptr;
    }

    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES; ++location)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];

        if(attr.enabled)
        {

           glEnableVertexAttribArray(GLuint(location));
           glVertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*) (attr.offset));
        }
    }


    // Release

    vao.release();
    vbo.release();
    if(ibo.isCreated())
        ibo.release();
}


void SubMesh::draw()
{
    int num_vertices = data_size /vertexFormat.size;
    vao.bind();
    if (indices_count > 0)
    {
        glDrawElements(GL_TRIANGLES,indices_count, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    vao.release();
}

void SubMesh::cleanup()
{
    if (vbo.isCreated()){vbo.destroy();}
    if(ibo.isCreated()){vbo.destroy();}
    if(vao.isCreated()){vao.destroy();}
}

