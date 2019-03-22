#include "ComponentShape.h"
ComponentShape::ComponentShape(GameObject* p, ComponentType t) : Component(p,t)
{
}

void ComponentShape::SetColor(QColor color)
{
    this->color = color;
}

void ComponentShape::ChangeType(ShapeType newType)
{
    if (type == newType) return;

    switch((int)type)
    {
    case (int)CIRCLE:
        r = 0.5f;
        break;
    case (int)RECTANGLE:
        w = 0.7f;
        h = 0.4f;
        break;
    }

    shapeType = newType;
}

ComponentShape::ShapeType ComponentShape::GetShapeType() const
{
    return shapeType;
}

float ComponentShape::GetRadius() const
{
    return r;
}
float ComponentShape::GetHeight() const
{
    return h;
}
float ComponentShape::GetWidth() const
{
    return w;
}
