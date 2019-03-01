#include "scene.h"
#include <iostream>

Scene::Scene(QObject *parent) : QObject(parent)
{

}

Scene::~Scene()
{

}

void Scene::OnAddObject(GameObject* obj)
{
    sceneObjects.push_back(obj);
    std::cout << obj->GetName().data() << std::endl;
}

void Scene::OnDeleteObject(GameObject *obj)
{

}
