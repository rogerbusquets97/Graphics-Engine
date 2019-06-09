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
    void SetHeightMap(QString path);

    inline QOpenGLTexture* GetNormalMap()const{return NormalMap;}
    inline QOpenGLTexture* GetDiffuse()const{return Diffuse;}
    inline QOpenGLTexture* GetHeightMap()const{return HeightMap;}
    inline QString GetDiffusePath() const {return diffusePath;}
    inline QString GetNormalPath() const {return normalPath;}
    inline QString GetHeightMapPath()const{return heightPath;}

    void SetDiffuseMirrored(bool aMirrored);
    void SetNormalMirrored(bool aMirrored);
    void SetHeightMapMirrored(bool aMirrored);


    inline void SetDiffuseActive(bool a) {diffuseActive = a;}
    inline void SetNormalActive(bool a){normalActive = a;}
    inline void SetParallaxActive(bool a){parallaxActive = a;}
    inline bool IsDiffuseActive(){return diffuseActive;}
    inline bool IsNormalActive(){return normalActive;}
    inline bool IsParallaxActive(){return parallaxActive;}
    inline void SetTilling(float x, float y){tilling.setX(x), tilling.setY(y);}

    inline QVector2D GetTilling()const{return tilling;}

    private:
    QOpenGLTexture* Diffuse;
    QOpenGLTexture* NormalMap;
    QOpenGLTexture* HeightMap;
    QString diffusePath;
    QString normalPath;
    QString heightPath;

    QVector2D tilling;

    bool diffuseActive = true;
    bool normalActive = true;
    bool parallaxActive = true;
};

#endif // MATERIAL_H
