#include "circlewidget.h"

#include <QPainter>

circlewidget::circlewidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground((true));
}

QSize circlewidget::sizeHint() const
{
    return QSize(256,256);
}
QSize circlewidget::minimumSizeHint() const {
    return QSize(64,64);
}

void circlewidget::paintEvent(QPaintEvent *event)
{
   /* QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);

    QPainter painter(this);

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

    int r= 24;
    int w =r*2, h=r*2;
    int x = rect().width() / 2 - r;
    int y = rect().height() / 2-r;
    QRect circleRect(x,y,w,h);
   painter.drawEllipse(circleRect);*/

}
