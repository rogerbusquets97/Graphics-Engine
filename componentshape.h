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
    BLUE = 0, WHITE, BLACK, RED, GREEN, MAGENTA, ORANGE, YELLOW, COLOR_UNKNOWN
};

enum StrokeType {
    SOLID = 0, DASH, DOT, DASHDOT, DASHDOTDOT, STROKE_UNKNOWN
};

class ComponentShape : public Component
{
public:

    ComponentShape(GameObject* p, ComponentType t);
    void SetColorType(ColorType color);
    void SetShapeType(ShapeType shapeType);
    void SetStrokeType(StrokeType strokeType);
    void SetRadius (int r);
    void SetWidth (int w);
    void SetHeight (int h);
    void SetPenWidth (int penWidth);
    ShapeType GetShapeType() const;
    ColorType GetColorType() const {return colorType;}
    StrokeType GetStrokeType() const { return strokeType;}
    int GetRadius() const { return r; }
    int GetHeight() const { return h; }
    int GetWidth() const { return w ; }
    int GetPenWidth() const { return penWidth; }
    int GetPositionX();
    int GetPositionY();

private:

    ColorType colorType;
    ShapeType shapeType;
    StrokeType strokeType;
    int penWidth;

    // CIRCLE
    int r;
    // RECTANGLE
    int w, h;
};


#endif // COMPONENTSHAPE_H
