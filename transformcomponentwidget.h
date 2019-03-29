#ifndef TRANSFORMCOMPONENTWIDGET_H
#define TRANSFORMCOMPONENTWIDGET_H

#include <QWidget>

namespace Ui {
class TransformComponentWidget;
}

class TransformComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformComponentWidget(QWidget *parent = nullptr);
    ~TransformComponentWidget();

public:
    Ui::TransformComponentWidget *ui;
};

#endif // TRANSFORMCOMPONENTWIDGET_H
