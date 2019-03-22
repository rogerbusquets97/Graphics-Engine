#include "inspector.h"
#include "component.h"

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{
    //Create subwidgets

    //Add them to the layout

}

void Inspector::SetObject(GameObject* obj)
{
    selected = obj;
}

GameObject* Inspector::GetObject()const
{
    return selected;
}
void Inspector::UpdateContent()
{
    if(selected!=nullptr)
    {
        for(QList<Component*>::iterator it = selected->components.begin(); it!= selected->components.end(); ++it)
        {
            switch ((*it)->GetType()) {
            case ComponentType::Shape:
                //Set visible shape component visible
                break;
            default:
                break;
            }
        }
    }
}
