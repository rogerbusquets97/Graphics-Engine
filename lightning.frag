#version 330 core

in Data
{
    vec2 TexCoords;
} FSIn;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

#define NR_POINT_LIGHTS 20
#define NR_DIREC_LIGHTS 5
#define NR_SPOT_LIGHTS 20

float ambientTerm = 0.5;
vec3 L = vec3(0,0,1);
vec3 lightColor = vec3(1,1,1);

struct DirLight
{
    vec3 position;
    float ambient;
    float diffuse;
    float specular;
    vec3 color;
};

struct PointLight
{
    vec3 position;
    float ambient;
    float diffuse;
    float specular;
    vec3 color;
};

struct SpotLight
{
    vec3 position;
    float ambient;
    float diffuse;
    float specular;
    vec3 color;

    float cutOff;
    float outerCutOff;
};

    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(void)
{
    vec3 fragPos = texture(gPosition, FSIn.TexCoords).rgb;
    vec3 fragNormal = texture(gNormal, FSIn.TexCoords).rgb;
    vec3 fragDiffuse = texture(gAlbedo, FSIn.TexCoords).rgb;


    vec3 ambient = fragDiffuse * ambientTerm;

    vec3 diffuse = fragDiffuse * dot(fragNormal, L);

    vec3 result;


    FragColor.rgb = ambient + diffuse;

    //GammaCorrection
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.4));
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 result;
    return result;
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 result;
    return result;
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 result;
    return result;
}
