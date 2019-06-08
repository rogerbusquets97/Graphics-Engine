#include "transform.h"

Transform::Transform(GameObject* p, ComponentType t)  : Component(p,t)
{
    position = Float3(0,0,0);
    rotation = Float3(0,0,0);
    scale = Float3(1,1,1);
}

void Transform::SetPosition(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}
void Transform::SetRotation(float x, float y, float z)
{
    this->rotation.x = x;
    this->rotation.y = y;
    this->rotation.z = z;
}

void Transform::SetScale(float x, float y, float z)
{
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}
