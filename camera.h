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

    void PrepareMatrices();

    int viewportWidth = 128;
    int viewportHeight = 128;

    float fovy = 60.0f;
    float znear = 0.1f;
    float zfar = 1000.0f;

    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    float speed = 10.0f;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    QVector3D eyePosition;
    QVector3D center;
    QVector3D up;
};

#endif // CAMERA_H
