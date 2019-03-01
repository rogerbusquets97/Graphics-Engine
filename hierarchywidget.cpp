#include "hierarchywidget.h"
#include "gameobjectwidget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "gameobjectwidget.h"

HierarchyWidget::HierarchyWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Inspector)
{
  //Aixi afegim go visualment.
  //  GameObjectWidget* obj_widget = new GameObjectWidget(GameObject*);


    QSpacerItem* spacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(spacer);

    setLayout(layout);



}

void HierarchyWidget::OnAddGameObject(GameObject* obj)
{
    if(obj!= nullptr)
    {
        GameObjectWidget* objWidget = new GameObjectWidget(nullptr, obj);
        layout()->addWidget(objWidget);
    }




}
