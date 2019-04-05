#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out Data
{
   vec3 color;
} VSOut;

void main(void)
{
        gl_Position = vec4(position,1);
        VSOut.color = color;
}
