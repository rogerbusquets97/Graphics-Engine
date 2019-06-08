#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoords;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec2 texCoords;
} VSOut;

void main()
{
    vec4 worldPos = modelMatrix * vec4(position, 1.0);
    VSOut.positionViewspace = worldPos.xyz;
    VSOut.texCoords = texCoords;

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    VSOut.normalViewspace = normalMatrix * normal;


    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
