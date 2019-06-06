#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QList>
#include <QString>
#include "componentshape.h"


class ComponentShape;
class Transform;
class GameObject : public QObject
{
    Q_OBJECT
public:
    GameObject(QObject *parent = nullptr, QString n = "GameObject");
    inline void SetName(const QString n){ name = n; }
    inline QString GetName() const { return name; }
    void Update();
public:
    QString name;
    QList<Component*> components;
    Component* GetComponent(ComponentType t);
    bool HasComponentOfType(ComponentType t);
    Transform* transform;
signals:

public slots:
    void OnAddComponent(Component* c);
    void OnDeleteComponent(Component* c);

};

#endif // GAMEOBJECT_H
