#include "ComponentShape.h"
ComponentShape::ComponentShape(GameObject* p, ComponentType t) : Component(p,t)
{
    shapeType = CIRCLE;
    colorType = WHITE;
}

void ComponentShape::ChangeType(ShapeType newType)
{
    if (shapeType == newType) return;

    switch(shapeType)
    {
    case CIRCLE:
        r = 0.5f;
        break;
    case RECTANGLE:
        w = 0.7f;
        h = 0.4f;
        break;
    default:
        break;
    }

    shapeType = newType;
}

ShapeType ComponentShape::GetShapeType() const
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
