#include "component.h"

Component::Component(GameObject* p, ComponentType t)
{
    type = t;
    parent = p;
}

Component::~Component()
{

}
