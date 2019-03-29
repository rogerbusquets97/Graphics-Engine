#include "shapewidget.h"
#include "mainwindow.h"
#include <iostream>
#include <QPainter>

ShapeWidget::ShapeWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

void ShapeWidget::AddComponentShape(ComponentShape* compShape)
{
    if(compShape!= nullptr)
    {
        compShapes.push_back(compShape);
    }
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
   QPainter painter(this);

   QBrush brush;
   QPen pen;
   brush.setColor(QColor::fromRgb(255,255,255));
   brush.setStyle(Qt::BrushStyle::SolidPattern);
   pen.setStyle(Qt::PenStyle::NoPen);
   painter.setBrush(brush);
   painter.setPen(pen);

   painter.drawRect(rect());

   for(int i = 0; i < compShapes.size(); ++i)
    {
        switch (compShapes[i]->GetShapeType())
        {
            case ShapeType::CIRCLE:
            {
                // CIRCLE Render properties -------
                brush.setColor(sortColor(compShapes[i]->GetColorType()));
                pen.setWidth(4);
                pen.setColor(sortColor(compShapes[i]->GetColorType()));
                pen.setStyle(Qt::PenStyle::DashLine);
                painter.setPen(pen);
                //---------
                int x_circle = compShapes[i]->GetPositionX();
                int y_circle = compShapes[i]->GetPositionY();

                int r_circle = compShapes[i]->GetRadius();
                int w_circle = r_circle *2;
                int h_circle = r_circle *2;

                QRect circleRect(x_circle,y_circle,w_circle, h_circle);
                painter.drawEllipse(circleRect);

                break;
            }
            case ShapeType::RECTANGLE:
            {
                // RECTANGLE Render properties -------
                brush.setColor(sortColor(compShapes[i]->GetColorType()));
                pen.setWidth(4);
                pen.setColor(sortColor(compShapes[i]->GetColorType()));
                pen.setStyle(Qt::PenStyle::DashLine);
                painter.setPen(pen);

                int x_rect = compShapes[i]->GetPositionX();
                int y_rect = compShapes[i]->GetPositionY();

                int w_rect = compShapes[i]->GetWidth();
                int h_rect = compShapes[i]->GetHeight();

                QRect rectRect(x_rect,y_rect,w_rect,h_rect);
                painter.drawRect(rectRect);
                break;
            }
            default:
            {
                std::cout << "It's the OA" << std::endl;
                break;
            }
        }
    }
    painter.end();
}

QColor ShapeWidget::sortColor(ColorType t)
{
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);
    QColor ret = whiteColor;

    switch(t)
    {
        case ColorType::BLUE:
        {
        ret = blueColor;
        break;
        }
    case ColorType::WHITE:
        {
        ret = whiteColor;
        break;
        }
    case ColorType::BLACK:
        {
        ret = blackColor;
        break;
        }
    default:
        {
        ret = whiteColor;
        break;
        }
    }
    return ret;
}

void ShapeWidget::ClearShapesToRender()
{
   compShapes.clear();
}
