#ifndef COMPONENTLIGHTWIDGET_H
#define COMPONENTLIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class ComponentLightWidget;
}

class ComponentLightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentLightWidget(QWidget *parent = nullptr);
    ~ComponentLightWidget();

private:
    Ui::ComponentLightWidget *ui;
};

#endif // COMPONENTLIGHTWIDGET_H
