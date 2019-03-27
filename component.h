#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include "gameobject.h"

 //De moment nomes tenim aquest
class GameObject;

class Component
{
public:
    enum ComponentType
    {
     Shape,
     Unknown
    };

    Component(GameObject* p, ComponentType t) : parent(p),type(t){}
    virtual ~Component();

    ComponentType GetType()const{return type;}
    GameObject* GetParent()const{return parent;}

protected:

    ComponentType type;
    GameObject* parent;

};

#endif // COMPONENT_H
