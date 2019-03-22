#include "inspector.h"

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{
    //Create subwidgets

    //Add them to the layout

}

void Inspector::SetComponentList(std::list<Component *> *components)
{
    this->components = components;
}
void Inspector::UpdateContent()
{
    if(components!=nullptr)
    {
        for(QList<Component*>::iterator it = *components.begin(); it!= *components.end(); ++it)
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
