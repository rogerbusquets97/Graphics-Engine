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
    private:
    QOpenGLTexture* Diffuse;
    QOpenGLTexture* NormalMap;
    QString diffusePath;
    QString normalPath;
};

#endif // MATERIAL_H