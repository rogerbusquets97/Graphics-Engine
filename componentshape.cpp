#include "ComponentShape.h"
ComponentShape::ComponentShape(GameObject* p, ComponentType t) : Component(p,t)
{
    shapeType = CIRCLE;
    colorType = BLUE;
    r = 25;
    w = 100;
    h = 100;
}

void ComponentShape::ChangeType(ShapeType newType)
{
    if (shapeType == newType) return;

    switch(shapeType)
    {
    case CIRCLE:
        r = 25;
        break;
    case RECTANGLE:
        w = 100;
        h = 100;
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
int ComponentShape::GetPositionX()
{
    return (int)parent->transform->GetPosition().x;
}
int ComponentShape::GetPositionY()
{
    return (int)parent->transform->GetPosition().y;
}
