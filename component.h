#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include "gameobject.h"

enum ComponentType {Shape}; //De moment nomes tenim aquest
class GameObject;

class Component
{
public:
    Component(GameObject* p, ComponentType t);
    virtual ~Component();

    ComponentType GetType()const{return type;}
    GameObject* GetParent()const{return parent;}

private:

    ComponentType type;
    GameObject* parent;

};

#endif // COMPONENT_H
