#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QList>
#include "ComponentShape.h"

class ShapeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShapeWidget(QWidget *parent = nullptr);
    void SetComponentShape(ComponentShape* comp_shape);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QList<ComponentShape*> GetShapes() { return compShapes; }
    void AddComponentShape(ComponentShape* compShape);
    void ClearShapesToRender();
private:
    void paintEvent(QPaintEvent *event) override;
    QColor sortColor(ColorType t);
    QList<ComponentShape*> compShapes;
signals:

public slots:
};

#endif // SHAPEWIDGET_H
