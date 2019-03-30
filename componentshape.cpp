#include "componentshape.h"
ComponentShape::ComponentShape(GameObject* p, ComponentType t) : Component(p,t)
{
    shapeType = CIRCLE;
    colorType = BLUE;
    strokeType = SOLID;
    penWidth = 4;
    r = 25;
    w = 100;
    h = 100;
}
void ComponentShape::SetColorType(ColorType color)
{
    this->colorType = color;
}

void ComponentShape::SetShapeType(ShapeType newType)
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

void ComponentShape::SetStrokeType(StrokeType stroke)
{
    this->strokeType = stroke;
}

void ComponentShape::SetRadius (int r)
{
    this->r = r;
}
void ComponentShape::SetWidth (int w)
{
    this->w = w;
}
void ComponentShape::SetHeight (int h)
{
    this->h = h;
}
void ComponentShape::SetPenWidth(int penWidth)
{
    this->penWidth = penWidth;
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
