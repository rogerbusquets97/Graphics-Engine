#ifndef MATERIAL_H
#define MATERIAL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>

class Material
{
public:
    Material();
    ~Material();
    void SetNormalMap(QString path);
    void SetDiffuse(QString path);

    inline QOpenGLTexture* GetNormalMap()const{return NormalMap;}
    inline QOpenGLTexture* GetDiffuse()const{return Diffuse;}
    inline QString GetDiffusePath() const {return diffusePath;}
    inline QString GetNormalPath() const {return normalPath;}

    void SetDiffuseMirrored(bool aMirrored);
    void SetNormalMirrored(bool aMirrored);


    inline void SetDiffuseActive(bool a) {diffuseActive = a;}
    inline void SetNormalActive(bool a){normalActive = a;}
    inline bool IsDiffuseActive(){return diffuseActive;}
    inline bool IsNormalActive(){return normalActive;}

    private:
    QOpenGLTexture* Diffuse;
    QOpenGLTexture* NormalMap;
    QString diffusePath;
    QString normalPath;

    bool diffuseActive = true;
    bool normalActive = true;
};

#endif // MATERIAL_H
