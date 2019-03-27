#include "inspector.h"
#include "component.h"

#include "QVBoxLayout"
#include "shapecomponentwidget.h"
#include "QSpacerItem"
#include "transformcomponentwidget.h"

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{

   //Subwidgets
   transformComponentWidget = new TransformComponentWidget();
   transformComponentWidget->setVisible(false);

   shapeCompoenentWidget = new ShapeComponentWidget();
   shapeCompoenentWidget->setVisible(false);

   QSpacerItem* spacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);

   //Add them to a vertical layout
   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(transformComponentWidget);
   layout->addWidget(shapeCompoenentWidget);


   //Spacer should be added last
   layout->addItem(spacer);

   //Set layout to use
   setLayout(layout);


}

void Inspector::SetObject(GameObject* obj)
{
    selected = obj;
    UpdateContent();
}

GameObject* Inspector::GetObject()const
{
    return selected;
}
void Inspector::UpdateContent()
{
    //Set all invisible before checking for available components
    shapeCompoenentWidget->setVisible(false);
     transformComponentWidget->setVisible(false);

    if(selected!=nullptr)
    {
        transformComponentWidget->setVisible(true);
        for(QList<Component*>::iterator it = selected->components.begin(); it!= selected->components.end(); ++it)
        {
            switch ((*it)->GetType()) {
            case ComponentType::Shape:
                //Set visible shape component
                shapeCompoenentWidget->setVisible(true);
                break;
            default:
                break;
            }
        }
    }
}
