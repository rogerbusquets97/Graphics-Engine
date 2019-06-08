#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec3 tangentLocalspace;
    vec3 bitangentLocalspace;
    vec3 normalLocalspace;
    vec2 texCoords;
} FSIn;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;
uniform mat4 modelMatrix;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = FSIn.positionViewspace;
    // also store the per-fragment normals into the gbuffer
    vec3 T = normalize(FSIn.tangentLocalspace);
    vec3 B = normalize(FSIn.bitangentLocalspace);
    vec3 N = normalize(FSIn.normalLocalspace);

    mat3 TBN = mat3(T, B, N);
    vec3 normalTangent = texture(normalMap, FSIn.texCoords).rgb;
    normalTangent = normalize(normalTangent * 2.0 - 1.0);

    vec3 normalLocal = normalize(TBN * normalTangent);
    vec3 normalView = normalize(modelMatrix * vec4(normalLocal, 0.0)).xyz;

    gNormal = normalView;
    // and the diffuse per-fragment color
    gAlbedo.rgb = texture(diffuseTexture, FSIn.texCoords * 0.1).rgb;
}
