#include "myopenglwidget.h"
#include "mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <QFile>
#include <QByteArray>
#include <iostream>
#include <QVector2D>
#include <vector>

Mesh::Mesh()
{
    material = new Material();
    needsUpdate =true;
}

Mesh::~Mesh()
{
    destroy();
}

void Mesh::update()
{
    if(needsUpdate)
    {
        for(int i = 0; i < submeshes.size(); ++i)
        {
            submeshes.at(i)->update();
        }
        needsUpdate = false;
    }
}

void Mesh::destroy()
{
    for(int i = 0; i < submeshes.size(); ++i)
    {
        if(submeshes[i] != nullptr)
            submeshes.clear();
    }
}

void Mesh::loadModel(const char *filename)
{
    if(!submeshes.empty())
    {
        destroy();
    }
    path = filename;
    Assimp::Importer import;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Could not open file for read: " << filename << std::endl;
        return;
    }

    QByteArray data = file.readAll();

    const aiScene *scene = import.ReadFileFromMemory(
                data.data(), data.size(),
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
                aiProcess_GenSmoothNormals |
                aiProcess_RemoveRedundantMaterials |
                aiProcess_OptimizeMeshes |
                aiProcess_PreTransformVertices |
                aiProcess_ImproveCacheLocality |
                aiProcess_CalcTangentSpace,
                ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR:: ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
    needsUpdate = true;
}

SubMesh* Mesh::processMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;

    std::vector<Vertex> vert;
    std::vector<unsigned int> ind;

    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        QVector3D vec;
        vec.setX(mesh->mVertices[i].x);
        vec.setY(mesh->mVertices[i].y);
        vec.setZ(mesh->mVertices[i].z);

        vertex.Position = vec;

        vec.setX(mesh->mNormals[i].x);
        vec.setY(mesh->mNormals[i].y);
        vec.setZ(mesh->mNormals[i].z);

        vertex.Normal = vec;

        if(mesh->mTextureCoords[0])
        {
            QVector2D vector;
            vector.setX(mesh->mTextureCoords[0][i].x);
            vector.setY(mesh->mTextureCoords[0][i].y);

            vertex.TexCoords = vector;
        }
        else
        {
            vertex.TexCoords = QVector2D(0,0);
        }

        vec.setX(mesh->mTangents[i].x);
        vec.setY(mesh->mTangents[i].y);
        vec.setZ(mesh->mTangents[i].z);

        vertex.Tangent = vec;

        vec.setX(mesh->mBitangents[i].x);
        vec.setY(mesh->mBitangents[i].y);
        vec.setZ(mesh->mBitangents[i].z);
        vertex.Bitangent = vec;


        vert.push_back(vertex);

    }

    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            ind.push_back(face.mIndices [j]);
        }
    }

    return new SubMesh(vert, ind);

}

void Mesh::draw()
{
    for(int i = 0; i < submeshes.size(); ++i)
    {
        submeshes.at(i)->draw();
    }
}

void Mesh::processNode(aiNode *node, const aiScene *scene)
{
    //process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        submeshes.push_back(processMesh(mesh, scene));
    }

    //then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
