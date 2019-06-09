#version 330 core

in Data
{
    vec2 TexCoords;
} FSIn;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 viewPos;

#define NR_POINT_LIGHTS 20
#define NR_DIREC_LIGHTS 5
#define NR_SPOT_LIGHTS 20

float ambientTerm = 0.3;
vec3 L = vec3(0,0.5,1);
vec3 lightColor = vec3(1,1,1);

struct DirLight
{
    vec3 position;
    vec3 direction;

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
    vec3 direction;

    float ambient;
    float diffuse;
    float specular;
    vec3 color;

    float cutOff;
    float outerCutOff;
};

    uniform DirLight dirLights[NR_DIREC_LIGHTS];
    uniform PointLight pointLights[NR_POINT_LIGHTS];
    uniform SpotLight spotLights[NR_SPOT_LIGHTS];

    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 fragPosition);
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(void)
{
    vec3 fragPos = texture(gPosition, FSIn.TexCoords).rgb;
    vec3 fragNormal = texture(gNormal, FSIn.TexCoords).rgb;
    vec3 fragDiffuse = texture(gAlbedo, FSIn.TexCoords).rgb;


    vec3 ambient = fragDiffuse * ambientTerm;

    vec3 diffuse = fragDiffuse * dot(fragNormal, L);

    // LIGHTING
    vec3 result = vec3(0.0, 0.0,0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    for (int i = 0; i < NR_DIREC_LIGHTS; i++)
    {
        result += CalcDirLight(dirLights[i], normal, viewDir, fragPos);
    }
    for (int k = 0; k < NR_POINT_LIGHTS; k++)
    {
        //result += CalcPointLight(pointLights[k], normal, fragPosarg, viewDir);
    }
    for (int j = 0; j < NR_SPOT_LIGHTS; j++)
    {
       // result += CalcSpotLight(spotLights[j], normal, fragPosarg, viewDir);
    }


    FragColor.rgb = (result + ambient) * diffuse;

    //GammaCorrection
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.4));
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 fragPosition)
{
    vec3 lightDir = normalize(light.position - fragPosition);

    vec3 vecAmbient = vec3(light.ambient, light.ambient, light.ambient);
    vec3 vecSpecular = vec3(light.specular, light.specular, light.specular);
    vec3 vecDiffuse = vec3(light.diffuse, light.diffuse, light.diffuse);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 ambient = vecAmbient * vec3(texture(gAlbedo, FSIn.TexCoords).rgb);
    vec3 diffuse = vecDiffuse * diff * vec3(texture(gAlbedo, FSIn.TexCoords).rgb);
    vec3 specular = vecSpecular * spec;
    return (ambient + diffuse + specular) * light.color;
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
