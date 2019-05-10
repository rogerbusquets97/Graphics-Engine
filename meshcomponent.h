#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "gameobject.h"
#include "component.h"
#include "mesh.h"

class MeshComponent : public Component
{
public:

    MeshComponent(Mesh* mesh, GameObject* p, ComponentType t);
    ~MeshComponent();
    void Update() override;
public:

    Mesh* mesh;
};

#endif // MESHCOMPONENT_H
