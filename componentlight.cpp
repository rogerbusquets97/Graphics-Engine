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
void componentlight::SetLightType()
{

}
void componentlight::SetTypeToDirectional()
{

}
void componentlight::SetTypeToSpot()
{

}
void componentlight::SetTypeToPoint()
{

}

void componentlight::setDiffuse(float diffuse)
{

}
float componentlight::GetDiffuse() const
{
    return diffuse;
}
void componentlight::setAmbient(float ambient)
{

}
float componentlight::GetAmbient() const
{
    return ambient;
}
void componentlight::setcutOff(float ambient)
{

}
float componentlight::GetCutOff() const
{
    return cutOff;
}
void componentlight::setOuterCutOff(float ambient)
{

}
float componentlight::GetOuterCutOff() const
{
    return outercutOff;
}
