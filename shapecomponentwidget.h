#ifndef SHAPECOMPONENTWIDGET_H
#define SHAPECOMPONENTWIDGET_H

#include <QWidget>

namespace Ui {
class ShapeComponentWidget;
}

class ShapeComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeComponentWidget(QWidget *parent = nullptr);
    ~ShapeComponentWidget();

private:
    Ui::ShapeComponentWidget *ui;
};

#endif // SHAPECOMPONENTWIDGET_H
