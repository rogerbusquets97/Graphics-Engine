#include "scene.h"
#include <iostream>
#include "mainwindow.h"
#include "inspector.h"
#include "shapewidget.h"

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
    // aixo no pot ser
    if (obj != nullptr)
    sceneObjects.push_back(obj);
}

void Scene::OnDeleteSelectedObject()
{
    if(selectedOject!=nullptr)
    {
        GameObject* toDelete = selectedOject;

        sceneObjects.removeOne(selectedOject);
        selectedOject = nullptr;

        for (int renderer_c = 0; renderer_c < w->shape_widget->GetShapes().size(); renderer_c++)
                w->shape_widget->GetShapes().removeOne(w->shape_widget->GetShapes()[renderer_c]);

        delete toDelete->transform;

        for (int i = 0; i < toDelete->components.size(); ++i) {
             delete toDelete->components[i];
        }

        if(toDelete!= nullptr)
        {
            delete toDelete;
        }
    }

}

void Scene::OnDeleteObject(QString name)
{
    GameObject* toDelete = GetObject(name);
    sceneObjects.removeOne(toDelete);

    for (int renderer_c = 0; renderer_c < w->shape_widget->GetShapes().size(); renderer_c++)
            w->shape_widget->GetShapes().removeOne(w->shape_widget->GetShapes()[renderer_c]);

    delete toDelete->transform;

    for (int i = 0; i < toDelete->components.size(); ++i) {
         delete toDelete->components[i];
    }

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
    else
    {
        selectedOject = nullptr;
        w->inspector->SetObject(nullptr);
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

