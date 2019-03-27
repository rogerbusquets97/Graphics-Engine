#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"

#include <QWidget>
#include <QPainter>

enum ShapeType {
    CIRCLE = 0, RECTANGLE, SHAPE_UNKNOWN
};
enum ColorType {
    BLUE = 0, WHITE, BLACK, COLOR_UNKNOWN
};

class ComponentShape : public Component
{
public:

    ComponentShape(GameObject* p, ComponentType t);
    void SetColor(QColor color);
    void ChangeType(ShapeType newType);
    ShapeType GetShapeType() const;
    float GetRadius() const;
    float GetHeight() const;
    float GetWidth() const;

private:

    ColorType colorType;
    ShapeType shapeType;
    QBrush brush;
    QPen pen;

    // CIRCLE
    float r;
    // RECTANGLE
    float w, h;
};


#endif // COMPONENTSHAPE_H
