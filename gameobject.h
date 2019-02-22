#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include "component.h"
#include <list>
#include <string>
class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = nullptr, std::string n);
    void SetName(const std::string n);
    inline std::string GetName() const {return name;}
private:
    std::string name;
    std::list<Component*> components;
signals:

public slots:
    void OnAddComponent(Component* c);
    void OnDeleteComponent(Component* c);

};

#endif // GAMEOBJECT_H
