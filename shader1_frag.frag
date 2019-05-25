#version 330 core

// Uniform inputs

uniform sampler2D Albedo;
uniform sampler2D NormalMap;
uniform mat4 worldViewMatrix;
in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec3 tangentLocalspace;
    vec3 bitangentLocalspace;
    vec3 normalLocalspace;
    vec2 texCoords;
} FSIn;

out vec4 outColor;
float ambientTerm = 0.05;
vec3 L = vec3(0,0,1);
vec3 lightColor = vec3(1,1,1);

void main(void)
{

    vec3 V = -normalize(FSIn.positionViewspace);

    // NORMAL MAPPING
    // Tangent to local (TBN) matrix
    vec3 T = normalize(FSIn.tangentLocalspace);
    vec3 B = normalize(FSIn.bitangentLocalspace);
    vec3 N = normalize(FSIn.normalLocalspace);
    mat3 TBN = mat3(T, B, N);


    // obtain normal from normal map in range [0,1]
    vec3 normalTangent = texture(NormalMap, FSIn.texCoords).rgb;
    // transform normal vector to range [-1,1]
    normalTangent = normalize(normalTangent * 2.0 - 1.0);
    vec3 normalLocal = normalize(TBN * normalTangent);

    // Convert normal from tangent space to local space and view space
    vec3 normalView = normalize(worldViewMatrix * vec4(normalLocal, 0.0)).xyz;
    vec3 albedo = texture(Albedo, FSIn.texCoords).rgb;
    // LIGHT
    vec3 ambient = albedo * ambientTerm;
    vec3 specular = lightColor * dot(normalView, normalize(V + L));
    vec3 diffuse = albedo * dot(normalView, L);


    outColor.rgb = ambient + diffuse;

    outColor.a = 1.0;

    // Gamma Correction
    outColor.rgb = pow(outColor.rgb, vec3(1.0/2.4));


}
