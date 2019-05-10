#include "meshcomponent.h"

MeshComponent::MeshComponent(Mesh* mesh, GameObject* p, ComponentType t) : Component(p,t)
{
    this->mesh = mesh;
}

MeshComponent::~MeshComponent()
{
    delete mesh;
}

void MeshComponent::Update()
{
    if(mesh != nullptr)
    {
        mesh->Draw();
    }
}
