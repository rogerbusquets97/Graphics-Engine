#include "shapewidget.h"


#include <QPainter>

ShapeWidget::ShapeWidget(QWidget *parent) : QWidget(parent)
{

}

void ShapeWidget::SetComponentShape(ComponentShape* comp_shape)
{
    shape = comp_shape;
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);

    QColor blueColor = QColor::fromRgb((127,190,220));
    QColor whiteColor = QColor::fromRgb((255,255,255));
    QColor blackColor = QColor::fromRgb((0,0,0));
    QBrush brush;
    QPen pen;

    brush.setColor((blueColor));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect());

    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setPen(pen);

    switch (shape->ComponentShape())
    {
    case ComponentShape::CIRCLE:
        int r = shape->GetRadius();
        int w = r*2, h = r*2;
        int x = rect().width() / 2 - r;
        int y = rect().height() / 2 - r;
        QRect circleRect(x,y,w,h);
        painter.drawEllipse(circleRect);
        break;
    }
    /*int r= 24;
    int w =r*2, h=r*2;
    int x = rect().width() / 2 - r;
    int y = rect().height() / 2-r;
    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);*/

}
