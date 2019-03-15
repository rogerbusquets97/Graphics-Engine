#include "gameobject.h"
#include "mainwindow.h"

GameObject::GameObject(QObject *parent, QString n) : QObject(parent), name(n)
{
}

void GameObject::OnAddComponent(Component* c)
{
    components.push_back(c);
}

void GameObject::OnDeleteComponent(Component* c)
{
    components.remove(c);
}
