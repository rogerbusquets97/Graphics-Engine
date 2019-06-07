#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out Data
{
   vec2 TexCoords;

} VSOut;

void main(void)
{
    VSOut.TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
