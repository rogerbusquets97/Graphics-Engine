#include "submesh.h"

#include <iostream>
#include "myopenglwidget.h"

extern QOpenGLFunctions_3_3_Core* gl;

/*SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices, int indices_count) :
    vertexFormat(vertexFormat),
    data((unsigned char*)data),
    data_size(size),
    indices(indices),
    indices_count(indices_count)
{
   program.create();
   program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert.vert");
   program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag.frag");
   program.link();
   program.bind();

   vao.create();
   vao.bind();

   if(this->data!= nullptr)
   {
       std::cout<< "Data" << std::endl;
       vbo.create();
       vbo.bind();
       vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
       vbo.allocate(this->data, size);
   }
   else
       return;

   if(this->indices!= nullptr)
   {
       std::cout<< "Indexes" << std::endl;
       ibo.create();
       ibo.bind();
       ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
       ibo.allocate(this->indices,sizeof(unsigned int) * indices_count);
   }

   for(int location = 0; location< MAX_VERTEX_ATTRIBUTES; ++location)
   {
       VertexAttribute &attribute = vertexFormat.attribute[location];
       if(attribute.enabled)
       {
           gl->glEnableVertexAttribArray(GLuint(location));
           gl->glVertexAttribPointer(GLuint(location), attribute.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)(attribute.offset));
       }
   }


   vao.release();
   vbo.release();

   if(ibo.isCreated())
       ibo.release();


  // update();
}*/

SubMesh::SubMesh(VertexFormat vertexFormat, void* d, size_t d_size, uint* indices, uint indices_count) :
                             vertexFormat(vertexFormat), data_size(d_size), indices_count(indices_count),
                             ibo(QOpenGLBuffer::Type::IndexBuffer)
{
    this->data = new byte[d_size];
    memcpy(data, d, d_size);
    this->indices = new unsigned int[indices_count];
    memcpy(this->indices, indices, indices_count * sizeof(unsigned int));
}

SubMesh::~SubMesh()
{

}
void SubMesh::update()
{
    // VAO: Vertex format description and stato of VBOs
    vao.create();
    vao.bind();

    //VBO: Buffer with vertex data
    if(data!=nullptr)
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

           gl->glEnableVertexAttribArray(GLuint(location));
           gl->glVertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*) (attr.offset));
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
        gl->glDrawElements(GL_TRIANGLES,indices_count, GL_UNSIGNED_INT, indices);
    }
    else
    {
        gl->glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    vao.release();
}

void SubMesh::cleanup()
{
    if (vbo.isCreated()){vbo.destroy();}
    if(ibo.isCreated()){vbo.destroy();}
    if(vao.isCreated()){vao.destroy();}
}

