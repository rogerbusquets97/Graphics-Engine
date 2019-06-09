#include "componentlight.h"

componentlight::componentlight(GameObject* p, ComponentType t) :  Component(p,t)
{
    color = Color(1.0, 1.0, 1.0);

    diffuse = 10.0f;
    ambient = 3.0f;
    specular = 10.0f;
    cutOff = 12.0f;
    outercutOff = 12.0f;
    SetTypeToPoint();
}


void componentlight::SetRGBColor(Color color)
{
        this->color.r = color.r;
        this->color.g = color.g;
        this->color.b = color.b;
}
Color componentlight::GetRGBColor() const
{
    return color;
}
float* componentlight::GetColorToEdit() const
{
    return (float*)&color;
}
LightType componentlight::GetLightType() const
{
    return lighttype;
}
void componentlight::SetLightType(LightType type)
{
    this->lighttype = type;
}
void componentlight::SetTypeToDirectional()
{
    ambient = 0.0;
    specular = 0.0;
    diffuse = 1.5;
    cutOff = 0;
    outercutOff = 0;
    lighttype = DIRECTIONAL_LIGHT;

    //App->renderer3D->AddLight(this);
}
void componentlight::SetTypeToSpot()
{
    ambient = 10.0;
    specular = 2.5;
    cutOff = 12.0f;
    outercutOff = 12.0f;
    lighttype = SPOT_LIGHT;
}
void componentlight::SetTypeToPoint()
{
    ambient = 2.5;
    specular = 2.5;
    cutOff = 0;
    outercutOff = 0;
    lighttype = POINT_LIGHT;
}

void componentlight::setDiffuse(float diffuse)
{
    this->diffuse = diffuse;
}
float componentlight::GetDiffuse() const
{
    return diffuse;
}
void componentlight::setAmbient(float ambient)
{
    this->ambient = ambient;
}
float componentlight::GetAmbient() const
{
    return ambient;
}
void componentlight::setcutOff(float cutOff)
{
    this->cutOff = cutOff;
}
float componentlight::GetCutOff() const
{
    return cutOff;
}
void componentlight::setOuterCutOff(float outerCutoff)
{
    this->outercutOff = outerCutoff;
}
float componentlight::GetOuterCutOff() const
{
    return outercutOff;
}
