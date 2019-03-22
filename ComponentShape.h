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
    ShapeType GetShape() const;
    float GetRadius() const {return r};
    float GetHeight() const {return h};
    float GetWidth() const {return w};
private:
    QColor color;
    Shape type;

    // CIRCLE
    float r;
    // RECTANGLE
    float w, h;
};


#endif // COMPONENTSHAPE_H
