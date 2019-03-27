#include "scene.h"
#include <iostream>
#include "mainwindow.h"
#include "inspector.h"

Scene::Scene(QObject *parent) : QObject(parent)
{
    selectedOject = nullptr;
}

Scene::~Scene()
{
   for(QList<GameObject*>::iterator it = sceneObjects.begin(); it!= sceneObjects.end(); ++it)
   {
       delete (*it);
   }
}

void Scene::OnAddObject(GameObject* obj)
{
    sceneObjects.push_back(obj);
    std::cout << obj->GetName().toStdString() << std::endl;
}

void Scene::OnDeleteSelectedObject()
{
    if(selectedOject!=nullptr)
    {
        sceneObjects.removeOne(selectedOject);
        selectedOject = nullptr;
    }

}

void Scene::OnDeleteObject(QString name)
{
    GameObject* toDelete = GetObject(name);
    sceneObjects.removeOne(toDelete);
    if(toDelete!= nullptr)
    {
        delete toDelete;
    }
}

GameObject* Scene::GetObject(QString name)
{
    for(QList<GameObject*>::iterator it = sceneObjects.begin(); it!= sceneObjects.end(); ++it)
    {
        if((*it)->GetName() == name)
        {
            return *it;
            break;
        }
    }

    return nullptr;
}
int Scene::GetSceneGoCount()const
{
    return sceneObjects.count();
}

void Scene::SetSelectedObject(QString n)
{
    selectedOject = GetObject(n);

}

void Scene::SetSelectedObjectByInt(int i)
{
    if(!sceneObjects.empty())
    {
        selectedOject = sceneObjects.at(i);
        w->inspector->SetObject(selectedOject);
    }
}

void Scene::ClearScene()
{
     selectedOject = nullptr;

     for(int i = 0; i < sceneObjects.size(); ++i)
        delete sceneObjects[i];

     sceneObjects.clear();

}

QList<GameObject*> Scene::GetGameObjects() const
{
    return sceneObjects;
}

