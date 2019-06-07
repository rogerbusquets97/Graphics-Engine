#version 330 core

in Data
{
    vec2 TexCoords;
} FSIn;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

void main(void)
{
    vec3 fragPos = texture(gPosition, FSIn.TexCoords).rgb;
    vec3 fragNormal = texture(gNormal, FSIn.TexCoords).rgb;
    vec3 fragDiffuse = texture(gAlbedo, FSIn.TexCoords).rgb;

    vec3 L = -normalize(fragPos);
    vec3 N = normalize(fragNormal);

    float kD = max(0.0, dot(L,N));
    FragColor.rgb = fragDiffuse*kD;
    FragColor.a = 1.0;

    //GammaCorrection
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.4));


    FragColor.rgb = fragNormal;
}
