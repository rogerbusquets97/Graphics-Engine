#include "material.h"

Material::Material()
{
    Diffuse = nullptr;
    NormalMap = nullptr;
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

    NormalMap = new QOpenGLTexture(normalMap.mirrored());
    NormalMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    NormalMap->setMagnificationFilter(QOpenGLTexture::Linear);

    normalPath = path;
}

void Material::SetDiffuse(QString path)
{
    QImage diffuse;
    diffuse.load(path);
    if(Diffuse != nullptr)
        delete Diffuse;

    Diffuse = new QOpenGLTexture(diffuse.mirrored());
    Diffuse->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    Diffuse->setMagnificationFilter(QOpenGLTexture::Linear);

    diffusePath = path;
}


