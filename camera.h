#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();

   /* QVector4D getleftRigthBottomTop();
    QVector3D screenPointToWorldRay(int x, int y);
    QVector3D screenDisplacementToWorldVector(int x0, int y0, int x1, int y1, const QVector3D& worldPoint);
    QVector2D worldToScreenPoint(const QVector3D& p);*/

    void PrepareMatrices();

    int viewportWidth = 128;
    int viewportHeight = 128;

    float fovy = 60.0f;
    float znear = 0.1f;
    float zfar = 1000.0f;

    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    float speed = 5.0f;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

};

#endif // CAMERA_H
