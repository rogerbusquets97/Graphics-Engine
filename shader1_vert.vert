#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoords;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

uniform mat4 projectionMatrix;
uniform mat4 worldViewMatrix;

out Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec3 tangentLocalspace;
    vec3 bitangentLocalspace;
    vec3 normalLocalspace;
    vec2 texCoords;
} VSOut;

void main(void)
{
    VSOut.positionViewspace = (worldViewMatrix * vec4(position, 1)).xyz;
    VSOut.normalViewspace = (worldViewMatrix * vec4(normal, 0)).xyz;

    //Normal mapping
    VSOut.tangentLocalspace = tangent;
    VSOut.bitangentLocalspace = bitangent;
    VSOut.normalLocalspace = normal;

    VSOut.texCoords = texCoords;
    mat4 wvp = projectionMatrix * worldViewMatrix;

    gl_Position = wvp * vec4(position, 1.0);


}
