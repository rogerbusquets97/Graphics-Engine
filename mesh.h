#ifndef MESH_H
#define MESH_H
#include "resource.h"
#include "QVector"
#include "submesh.h"

//Assimp
#include "assimp/scene.h"
//Files
#include <QFile>
#include <QByteArray>
#include <QIODevice>

class Mesh : public Resource
{
public:
    Mesh();
    virtual ~Mesh() override;

    void update() override;
    void cleanup() override{}

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
    void loadModel(const char*filename);
    void Draw();
    void destroy();

    QVector<SubMesh*> submeshes;
    bool needsUpdate;

private:
    //Assimp stuff
    void processNode(aiNode *node, const aiScene *scene);
    SubMesh *processMesh(aiMesh *mesh, const aiScene *scene);

};

#endif // MESH_H
