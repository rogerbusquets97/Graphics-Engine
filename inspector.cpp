#include "inspector.h"
#include "component.h"

#include "QVBoxLayout"
#include "shapecomponentwidget.h"
#include "QSpacerItem"
#include "transformcomponentwidget.h"
#include "ComponentShape.h"
#include <iostream>


Inspector::Inspector(QWidget *parent) : QWidget(parent)
{

   //Subwidgets
   transformComponentWidget = new TransformComponentWidget();
   transformComponentWidget->setVisible(false);

   shapeCompoenentWidget = new ShapeComponentWidget();


   //Add them to a vertical layout
   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(transformComponentWidget);
   layout->addWidget(shapeCompoenentWidget);


   //Combo box for adding Components
   comboBox = new QComboBox();
   comboBox->addItem("Shape Component"); // Only shape for now
   layout->addWidget(comboBox);
   //Button to add Components
   button = new QPushButton();
   button->setText("Add Component");
   connect(button,SIGNAL(clicked()),this,SLOT(OnAddComponent()));
   layout->addWidget(button);
   //Spacer should be added last
   QSpacerItem* spacer = new QSpacerItem(1,0,QSizePolicy::Minimum, QSizePolicy::Minimum);
   layout->addItem(spacer);
   //Set layout to use
   setLayout(layout);

   SetAllInvisible();


}

void Inspector::OnAddComponent()
{
    std::cout<< "OnAddComponent" << std::endl;
    if(selected!= nullptr)
    {
        if(comboBox->currentText() == "Shape Component")
        {
            selected->OnAddComponent(new ComponentShape(selected,ComponentType::Shape));
        }
        //other components

        UpdateContent();

    }
}

void Inspector::SetAllInvisible()
{
    transformComponentWidget->setVisible(false);
    shapeCompoenentWidget->setVisible(false);
    comboBox->setVisible(false);
    button->setVisible(false);

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
        button->setVisible(true);
        comboBox->setVisible(true);
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
    else
    {
        SetAllInvisible();
    }
}
