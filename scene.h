#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QList>.h>
#include "gameobject.h"

class Scene : public QObject
{
    Q_OBJECT
public:
   Scene(QObject *parent = nullptr);
   virtual ~Scene();

private:
   QList<GameObject*> sceneObjects;


signals:

public slots:

   void OnAddObject(GameObject* obj);
   void OnDeleteObject(GameObject* obj);
};

#endif // SCENE_H
