#include "ComponentShape.h"
ComponentShape::ComponentShape(GameObject* p, ComponentType t)
{
    this->parent = p;
    this->type = t;
}

void ComponentShape::SetColor(QColor color)
{
    this->color = color;
}

void ComponentShape::ChangeType(Shape newType)
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
