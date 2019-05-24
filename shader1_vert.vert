#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;


uniform mat4 projectionMatrix;
uniform mat4 worldViewMatrix;

out Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
} VSOut;

void main(void)
{
    VSOut.positionViewspace = (worldViewMatrix * vec4(position, 1)).xyz;
    VSOut.normalViewspace = (worldViewMatrix * vec4(normal, 0)).xyz;

    mat4 wp = projectionMatrix * worldViewMatrix;

    gl_Position = wp * vec4(position, 1.0);
}
