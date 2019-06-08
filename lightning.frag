#version 330 core

in Data
{
    vec2 TexCoords;
} FSIn;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;


float ambientTerm = 0.5;
vec3 L = vec3(0,0,1);
vec3 lightColor = vec3(1,1,1);

void main(void)
{
    vec3 fragPos = texture(gPosition, FSIn.TexCoords).rgb;
    vec3 fragNormal = texture(gNormal, FSIn.TexCoords).rgb;
    vec3 fragDiffuse = texture(gAlbedo, FSIn.TexCoords).rgb;


    vec3 ambient = fragDiffuse * ambientTerm;

    vec3 diffuse = fragDiffuse * dot(fragNormal, L);

    FragColor.rgb = ambient + diffuse;

    /*outColor.a = 1.0;
    vec3 N = normalize(fragNormal);

    float kD = max(0.0, dot(L,N));
    FragColor.rgb = fragDiffuse*kD;
    FragColor.a = 1.0;*/

    //GammaCorrection
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.4));


    //FragColor.rgb = fragDiffuse;
}
