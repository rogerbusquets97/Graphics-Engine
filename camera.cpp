#include "camera.h"

Camera::Camera()
{

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
}
