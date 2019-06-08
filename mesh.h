#ifndef MESH_H
#define MESH_H

#include "resource.h"
#include "vertex.h"
#include "submesh.h"
#include "assimp/scene.h"
#include "material.h"
#include <QVector>
#include "gameobject.h"

class Resource;

class Mesh : public Resource
{
public:
    Mesh(GameObject* parent);
    ~Mesh(); //override;

    void update(); //override;
    void destroy(); //override;

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
    void loadModel(const char *filename);
    inline QString GetPath(){return path;}
    inline Material* GetMaterial(){return material;}
    inline GameObject* GetParent(){return parent;}
    void draw();

    QVector<SubMesh*> submeshes;
    bool needsUpdate;

private:

    //Assimp
    void processNode(aiNode *node, const aiScene *scene);
    SubMesh * processMesh(aiMesh *mesh, const aiScene *scene);
    QString path;
    Material* material;
    GameObject* parent;
};

#endif // MESH_H
