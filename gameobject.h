#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QList>
#include <QString>

enum ComponentType
{
 Shape,
 Component_Unknow
};

class Component;
class ComponentShape;
class GameObject : public QObject
{
    Q_OBJECT
public:
    GameObject(QObject *parent = nullptr, QString n = "GameObject");
    inline void SetName(const QString n){ name = n; }
    inline QString GetName() const { return name; }

public:
    QString name;
    QList<Component*> components;
    Component* GetComponent(ComponentType t);
signals:

public slots:
    void OnAddComponent(Component* c);
    void OnDeleteComponent(Component* c);

};

#endif // GAMEOBJECT_H
