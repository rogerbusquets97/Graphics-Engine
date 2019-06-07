#ifndef MESH_H
#define MESH_H

#include "resource.h"
#include "vertex.h"
#include "submesh.h"
#include "assimp/scene.h"
#include "material.h"

#include <QVector>

class Resource;
class GameObject;

class Mesh : public Resource
{
public:
    Mesh();
    ~Mesh(); //override;

    //Mesh * asMesh() override { return this; }

    void update(); //override;
    void destroy(); //override;

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
    void loadModel(const char *filename);
    inline QString GetPath(){return path;}
    inline Material* GetMaterial(){return material;}

    void draw();

    QVector<SubMesh*> submeshes;
    bool needsUpdate;

    GameObject* GetParent(){ return parent; }
    void SetParent(GameObject* go) { parent = go;}

private:
    GameObject* parent;
    //Assimp
    void processNode(aiNode *node, const aiScene *scene);
    SubMesh * processMesh(aiMesh *mesh, const aiScene *scene);
    QString path;
    Material* material;
};

#endif // MESH_H
