#include "gameobjectwidget.h"

GameObjectWidget::GameObjectWidget(QWidget *parent, GameObject* obj) : QWidget(parent), object(obj)
{
    label = new QLabel();
    if(object!= nullptr)
    {
        label->setText(object->GetName());
    }
}


