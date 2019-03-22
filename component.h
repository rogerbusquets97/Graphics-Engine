#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

enum ComponentType {Shape}; //De moment nomes tenim aquest

class Component
{
public:
    Component();
    virtual ~Component();
    ComponentType type;

    void inline SetType(ComponentType t){type = t;}
    ComponentType inline GetType()const{return type;}
};

#endif // COMPONENT_H
