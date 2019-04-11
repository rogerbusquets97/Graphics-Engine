#ifndef MESH_H
#define MESH_H
#include "resource.h"
#include "QVector"
#include "submesh.h"

class Mesh : public Resource
{
public:
    Mesh();
    virtual ~Mesh() override;

    void update() override;
    void cleanup() override;

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
    void loadModel(const char*filename);

    QVector<SubMesh*> submeshes;

private:
    //Assimp stuff
};

#endif // MESH_H
