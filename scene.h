#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QList>
#include <QString>
#include "componentlight.h"
#include "gameobject.h"
#include "mesh.h"

class Scene : public QObject
{
    Q_OBJECT
public:
   Scene(QObject *parent = nullptr);
   GameObject* GetObject(QString name);
   int GetSceneGoCount()const;
   void SetSelectedObject(QString n);
   void SetSelectedObjectByInt(int i);
   const QList<GameObject*>& GetObjectsList() const;
   void GetSceneMeshes(QList<Mesh*>& meshList)const;
   void GetSceneLights(QVector<componentlight*> &lights) const;
   void Update();
   virtual ~Scene();

private:
   QList<GameObject*> sceneObjects;
   GameObject* selectedOject;


signals:

public slots:

   void OnAddObject(GameObject* obj);
   void OnDeleteSelectedObject();
   void OnDeleteObject(QString name);

   void ClearScene();

   QList<GameObject*> GetGameObjects() const;

};

#endif // SCENE_H
