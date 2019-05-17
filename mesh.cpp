#include "assimp/Importer.hpp"
#include "assimp/Defines.h"
#include "assimp/postprocess.h"
//Other libraries
#include <stdio.h>
#include <iostream>
//
#include "mesh.h"
#include <QVector>

Mesh::Mesh()
{
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

void Mesh::loadModel(const char* path)
{
    Assimp::Importer import;

        QFile file(path);
        if(!file.open(QIODevice::ReadOnly))
        {
            std::cout << "Could not open file for read: " << path << std::endl;
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

void Mesh:: processNode(aiNode *node, const aiScene *scene)
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

SubMesh* Mesh::processMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
       QVector<unsigned int> indices;

       // Process vertices
       for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
       {
           vertices.push_back(mesh->mVertices[i].x);
           vertices.push_back(mesh->mVertices[i].y);
           vertices.push_back(mesh->mVertices[i].z);
           vertices.push_back(mesh->mNormals[i].x);
           vertices.push_back(mesh->mNormals[i].y);
           vertices.push_back(mesh->mNormals[i].z);

           if(mesh->mTextureCoords[0])
           {
               vertices.push_back(mesh->mTextureCoords[0][i].x);
               vertices.push_back(mesh->mTextureCoords[0][i].y);
           }

           if(mesh->mTangents != nullptr && mesh->mBitangents != nullptr)
           {
               vertices.push_back(mesh->mTangents[i].x);
               vertices.push_back(mesh->mTangents[i].y);
               vertices.push_back(mesh->mTangents[i].z);
               vertices.push_back(mesh->mBitangents[i].x);
               vertices.push_back(mesh->mBitangents[i].y);
               vertices.push_back(mesh->mBitangents[i].z);
           }
       }

       // Process indices
       for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
       {
           aiFace face = mesh->mFaces[i];
           for(unsigned int j = 0; j < face.mNumIndices; ++j)
           {
               indices.push_back(face.mIndices[j]);
           }
       }

       VertexFormat vertex_format;
       vertex_format.setVertexAttribute(0, 0, 3);
       vertex_format.setVertexAttribute(1, 3 * sizeof(float), 3);

       if(mesh->mTextureCoords[0])
       {
           vertex_format.setVertexAttribute(2, 6 *sizeof(float), 2);
       }

       if(mesh->mTangents != nullptr && mesh->mBitangents != nullptr)
       {
           vertex_format.setVertexAttribute(3, 9 *sizeof(float), 6);
       }

       return new SubMesh(vertex_format, vertices.data(), vertices.size() * sizeof(float), indices.data(), indices.size());
}

void Mesh::Draw()
{
    for(int i = 0; i<submeshes.length(); ++i)
    {
        submeshes[i]->draw();
    }
}
