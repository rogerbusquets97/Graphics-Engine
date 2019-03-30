#ifndef SHAPECOMPONENTWIDGET_H
#define SHAPECOMPONENTWIDGET_H

#include <QWidget>
#include "componentshape.h"

namespace Ui {
class ShapeComponentWidget;
}

class ShapeComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeComponentWidget(QWidget *parent = nullptr);
    ~ShapeComponentWidget();
    void SetComponentShape(ComponentShape* shape){this->shape = shape;}
    ComponentShape* GetComponentShape()const{return shape;}
    void Update();

    Ui::ShapeComponentWidget *ui;
private:

    ComponentShape* shape;
};

#endif // SHAPECOMPONENTWIDGET_H
