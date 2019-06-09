#ifndef COMPONENTLIGHT_H
#define COMPONENTLIGHT_H

#include "component.h"

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

enum LightType {
    DIRECTIONAL_LIGHT = 0,
    POINT_LIGHT,
    SPOT_LIGHT,
    UNKNOWN_LIGHT
};

class componentlight : public Component
{
public:
    componentlight(GameObject* p, ComponentType t);

    void SetRGBColor(Float3 color);
    Float3 GetRGBColor() const;
    float* GetColorToEdit() const;
    LightType GetLightType() const;
    void SetLightType(LightType type);
    void SetTypeToDirectional();
    void SetTypeToSpot();
    void SetTypeToPoint();

    void setDiffuse(float diffuse);
    float GetDiffuse() const;
    void setAmbient(float ambient);
    float GetAmbient() const;
    void setcutOff(float ambient);
    float GetCutOff() const;
    void setOuterCutOff(float ambient);
    float GetOuterCutOff() const;

private:
   Float3 color;
   LightType type;

   float diffuse = 10.0f;
   float ambient = 3.0f;
   float specular = 10.0f;
   float cutOff = 12.0f;
   float outercutOff = 12.0f;
};

#endif // COMPONENTLIGHT_H
