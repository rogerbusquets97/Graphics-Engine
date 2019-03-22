#include "shapewidget.h"


#include <QPainter>

ShapeWidget::ShapeWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground((true));
}

void ShapeWidget::SetComponentShape(ComponentShape* comp_shape)
{
    shape = comp_shape;
}

QSize ShapeWidget::sizeHint() const
{
    return QSize(256,256);
}
QSize ShapeWidget::minimumSizeHint() const {
    return QSize(64,64);
}


void ShapeWidget::paintEvent(QPaintEvent *event)
{
   // if (shape == nullptr) return;

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

   /* switch (shape->GetShapeType())
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

    int r= 24;
    int w =r*2, h=r*2;
    int x = rect().width() / 2 - r;
    int y = rect().height() / 2-r;
    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);


    int r2= 45;
    int w2 =r2*2, h2=r*2;
    int x2 = rect().width() / 2 - r2;
    int y2 = rect().height() / 2-r2;
    QRect circleRect2(x2,y2,w2,h2);
    painter.drawEllipse(circleRect2);
}
