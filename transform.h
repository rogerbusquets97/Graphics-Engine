#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "component.h"
#include "gameobject.h"

struct Float3
{
    Float3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Float3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    float x,y,z;
};

class Transform : public Component
{
public:
    Transform(GameObject* p, ComponentType t);
    inline Float3 GetPosition()const{return position;}
    inline Float3 GetRotation()const{return rotation;}
    inline Float3 GetScale()const{return scale;}

    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetScale(float x, float y, float z);
private:
    Float3 position;
    Float3 rotation;
    Float3 scale;
};

#endif // TRANSFORM_H
