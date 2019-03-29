#ifndef COMPONENTSHAPE_H
#define COMPONENTSHAPE_H

#include "component.h"
#include "transform.h"

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
    ColorType GetColorType() const {return colorType;}
    int GetRadius() const { return r; }
    int GetHeight() const { return h; }
    int GetWidth() const { return w ; }
    int GetPositionX();
    int GetPositionY();

private:

    ColorType colorType;
    ShapeType shapeType;


    // CIRCLE
    int r;
    // RECTANGLE
    int w, h;
};


#endif // COMPONENTSHAPE_H
