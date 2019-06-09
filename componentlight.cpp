#include "componentlight.h"

componentlight::componentlight(GameObject* p, ComponentType t) :  Component(p,t)
{
    color = Float3(1.0, 1.0, 1.0);

    diffuse = 10.0f;
    ambient = 3.0f;
    specular = 10.0f;
    cutOff = 12.0f;
    outercutOff = 12.0f;
}


void componentlight::SetRGBColor(Float3 color)
{
        this->color.x = color.x;
        this->color.y = color.y;
        this->color.z = color.z;
}
Float3 componentlight::GetRGBColor() const
{
    return color;
}
float* componentlight::GetColorToEdit() const
{
    return (float*)&color;
}
LightType componentlight::GetLightType() const
{
    return type;
}
void componentlight::SetLightType(LightType type)
{
    this->type = type;
}
void componentlight::SetTypeToDirectional()
{
    ambient = 0.0;
    specular = 0.0;
    diffuse = 1.5;
    cutOff = 0;
    outercutOff = 0;
    type = DIRECTIONAL_LIGHT;

    //App->renderer3D->AddLight(this);
}
void componentlight::SetTypeToSpot()
{
    ambient = 10.0;
    specular = 2.5;
    cutOff = 12.0f;
    outercutOff = 12.0f;
    type = SPOT_LIGHT;
}
void componentlight::SetTypeToPoint()
{
    ambient = 2.5;
    specular = 2.5;
    cutOff = 0;
    outercutOff = 0;
    type = POINT_LIGHT;
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
