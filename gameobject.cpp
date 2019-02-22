#include "gameobject.h"

GameObject::GameObject(QObject *parent, std::string n) : QObject(parent), name(n)
{

}

void GameObject::SetName(const std::string n)
{
    name = n;
}

void GameObject::OnAddComponent(Component* c)
{
    components.push_back(c);
}

void GameObject::OnDeleteComponent(Component* c)
{
    components.remove(c);
}
