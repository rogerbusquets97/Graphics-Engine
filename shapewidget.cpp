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
        std::cout << "Rendering shape of object: " << compShape->GetParent()->GetName().toStdString() << std::endl;
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
   // if (shape == nullptr) return;
   std::cout << "called paintevent" << compShapes.size()  << std::endl;
   QPainter painter(this);

    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);
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

    for(int i = 0; i < compShapes.size(); ++i)
    {
        std::cout << "I see sumn" << std::endl;
        switch (compShapes[i]->GetShapeType())
        {
            case ShapeType::CIRCLE:
            {
                std::cout << "It's a CIRLCE" << std::endl;
                int r= 24;
                int w =r*2, h=r*2;
                int x = rect().width() / 2 - r;
                int y = rect().height() / 2-r;
                QRect circleRect(x,y,w,h);
                painter.drawEllipse(circleRect);
                break;
            }
            case ShapeType::RECTANGLE:
        {
               std::cout << "It's a RECTANGLE" << std::endl;
            int w2 = 20;
            int h2 = 10;
            int x2 = 0;
            int y2 = 0;
            QRect rectRect(x2,y2,w2,h2);
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
