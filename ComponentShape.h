#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"

#include <QWidget>

class ComponentShape : public Component
{
public:
    enum Shape {
        CIRCLE = 0, RECTANGLE, UNKNOWN
    };

    ComponentShape(GameObject* p, ComponentType t);
    void SetColor(QColor color);
    void SetRect(QRect rect);
    void ChangeType(ComponentShape::Shape newType);
private:
    QColor color;
    Shape type;

    // CIRCLE
    int r;
    // RECTANGLE
    int w, h;
};


#endif // COMPONENTSHAPE_H
