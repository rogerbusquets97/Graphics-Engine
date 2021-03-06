#include "material.h"
#include <iostream>
Material::Material()
{
    Diffuse = nullptr;
    NormalMap = nullptr;
    HeightMap = nullptr;

    tilling = {1.0, 1.0};
    HeightScale = 0.1;
}

Material::~Material()
{
    if(NormalMap != nullptr)
        delete NormalMap;
    if(Diffuse != nullptr)
        delete Diffuse;
}
void Material::SetNormalMap(QString path)
{
    QImage normalMap;
    normalMap.load(path);
    if(NormalMap != nullptr)
        delete NormalMap;

    NormalMap = new QOpenGLTexture(normalMap);
    NormalMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    NormalMap->setMagnificationFilter(QOpenGLTexture::Linear);

    normalPath = path;
}

void Material::SetDiffuseMirrored(bool aMirrored)
{

    if(Diffuse != nullptr)
    {
        if(!diffusePath.isEmpty())
        {
            delete Diffuse;
            QImage diffuse;
            diffuse.load(diffusePath);
            if(aMirrored)
                Diffuse = new QOpenGLTexture(diffuse.mirrored());
            else
                Diffuse = new QOpenGLTexture(diffuse);

            Diffuse->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            Diffuse->setMagnificationFilter(QOpenGLTexture::Linear);
        }
        else
        {
            std::cout<<"Path empty"<<std::endl;
        }
    }


}

void Material::SetNormalMirrored(bool aMirrored)
{
    if(NormalMap != nullptr)
    {
        if(!normalPath.isEmpty())
        {
            delete NormalMap;
            QImage normal;
            normal.load(normalPath);
            if(aMirrored)
                NormalMap = new QOpenGLTexture(normal.mirrored());
            else
                NormalMap = new QOpenGLTexture(normal);

            NormalMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            NormalMap->setMagnificationFilter(QOpenGLTexture::Linear);
        }
        else
        {
            std::cout<<"Path empty"<<std::endl;
        }
    }
}

void Material::SetHeightMapMirrored(bool aMirrored)
{
    if(HeightMap != nullptr)
    {
        if(!heightPath.isEmpty())
        {
            delete HeightMap;
            QImage normal;
            normal.load(heightPath);
            if(aMirrored)
                HeightMap = new QOpenGLTexture(normal.mirrored());
            else
                HeightMap = new QOpenGLTexture(normal);

            HeightMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            HeightMap->setMagnificationFilter(QOpenGLTexture::Linear);
        }
        else
        {
            std::cout<<"Path empty"<<std::endl;
        }
    }
}
void Material::SetDiffuse(QString path)
{
    QImage diffuse;
    diffuse.load(path);
    if(Diffuse != nullptr)
        delete Diffuse;

    Diffuse = new QOpenGLTexture(diffuse);
    Diffuse->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    Diffuse->setMagnificationFilter(QOpenGLTexture::Linear);

    diffusePath = path;
}

void Material::SetHeightMap(QString path)
{
    QImage height;
    height.load(path);
    if(HeightMap != nullptr)
        delete HeightMap;

    HeightMap = new QOpenGLTexture(height);
    HeightMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    HeightMap->setMagnificationFilter(QOpenGLTexture::Linear);

    heightPath = path;
}


