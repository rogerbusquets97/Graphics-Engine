#include "ComponentShape.h"
ComponentShape::ComponentShape()
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
        r = 0.5;
        break;
    case (int)RECTANGLE:
        w = 0.7;
        h = 0.4;
        break;
    }

    type = newType;
}

ComponentShape::ShapeType ComponentShape::GetShape() const
{
    return type;
}
