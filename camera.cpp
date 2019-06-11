#include "camera.h"

Camera::Camera()
{
    eyePosition = {5.0,5.0,10.0};
    center = {0.0,0.0,0.0};
    up = {0.0,1.0,0.0};
}

void Camera::PrepareMatrices()
{
    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw, QVector3D(0.0,1.0,0.0));
    worldMatrix.rotate(pitch, QVector3D(1.0,0.0,0.0));

    viewMatrix = worldMatrix.inverted();

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy, float(viewportWidth)/viewportHeight, znear, zfar);

    viewMatrix.lookAt(eyePosition, center, up);
}
