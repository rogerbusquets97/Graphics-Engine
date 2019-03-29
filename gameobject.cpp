#include "gameobject.h"
#include "mainwindow.h"
#include "component.h"
#include "transform.h"

GameObject::GameObject(QObject *parent, QString n) : QObject(parent), name(n)
{
    transform = new Transform(this, ComponentType::Trans);
}

void GameObject::OnAddComponent(Component* c)
{
    components.push_back(c);
}

void GameObject::OnDeleteComponent(Component* c)
{
    components.removeOne(c);
}

Component* GameObject::GetComponent(ComponentType t)
{
    Component* ret = nullptr;

    for(int i = 0; i < components.size(); ++i)
        if(components[i]->GetType() == t)
                ret = components[i];
    return ret;
}
