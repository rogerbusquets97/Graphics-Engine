#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

enum ComponentType
{
 Shape,
 Trans,
 mesh,
 Component_Unknow
};

 //De moment nomes tenim aquest
class GameObject;
class Component
{
public:


    Component(GameObject* p, ComponentType t) : parent(p),type(t){}
    virtual ~Component();

    ComponentType GetType()const{return type;}
    GameObject* GetParent()const{return parent;}
    virtual void Update(){}

protected:

    ComponentType type;
    GameObject* parent;

};

#endif // COMPONENT_H
