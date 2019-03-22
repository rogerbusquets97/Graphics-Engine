#include "inspector.h"
#include "component.h"

#include "QBoxLayout"

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{
    //Create subwidgets
    shappowidgetto = new ComponentShapeWidget();

    //Add them to the layout
    QBoxLayout* votavox = new QBoxLayout(QBoxLayout::TopToBottom);

    votavox->addWidget(shappowidgetto);
    setLayout(votavox);

    shappowidgetto->setVisible((false));
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
    shappowidgetto->setVisible((false));
    if(selected!=nullptr)
    {
        for(QList<Component*>::iterator it = selected->components.begin(); it!= selected->components.end(); ++it)
        {
            switch ((*it)->GetType()) {
            case ComponentType::Shape:
                //Set visible shape component visible
                shappowidgetto->setVisible((true));
                break;
            default:
                break;
            }
        }
    }
}
