#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"

#include <QWidget>

class ComponentShape : public Component
{
public:
    enum ShapeType {
        CIRCLE = 0, RECTANGLE, UNKNOWN
    };

    ComponentShape(GameObject* p, ComponentType t);
    void SetColor(QColor color);
    void ChangeType(ComponentShape::ShapeType newType);
    ShapeType GetShapeType() const;
    float GetRadius() const;
    float GetHeight() const;
    float GetWidth() const;
private:
    QColor color;
    ShapeType shapeType;

    // CIRCLE
    float r;
    // RECTANGLE
    float w, h;
};


#endif // COMPONENTSHAPE_H
