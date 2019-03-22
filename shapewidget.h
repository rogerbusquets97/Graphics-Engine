#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QObject>
#include <QWidget>
#include "ComponentShape.h"

class ShapeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShapeWidget(QWidget *parent = nullptr);
    void SetComponentShape(ComponentShape* comp_shape);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
private:
    void paintEvent(QPaintEvent *event) override;


    ComponentShape* shape;
signals:

public slots:
};

#endif // SHAPEWIDGET_H
