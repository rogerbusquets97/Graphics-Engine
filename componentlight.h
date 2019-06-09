#ifndef COMPONENTLIGHT_H
#define COMPONENTLIGHT_H

#include "component.h"

struct Color
{
    Color(float x, float y, float z)
    {
        this->r = x;
        this->g = y;
        this->b = z;
    }
    Color()
    {
        r = 0;
        g = 0;
        b = 0;
    }
    float r,g,b;
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

    void SetRGBColor(Color color);
    Color GetRGBColor() const;
    float* GetColorToEdit() const;
    LightType GetLightType() const;
    void SetLightType(LightType lighttype);
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
   Color color;
   LightType lighttype;

   float diffuse = 10.0f;
   float ambient = 3.0f;
   float specular = 10.0f;
   float cutOff = 12.0f;
   float outercutOff = 12.0f;
};

#endif // COMPONENTLIGHT_H
