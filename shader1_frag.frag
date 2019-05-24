#version 330 core

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
} FSIn;

out vec4 outColor;
float ambientTerm = 0.5;

void main(void)
{
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
    return;

    vec3 L = -normalize(FSIn.positionViewspace);
    vec3 N = normalize(FSIn.normalViewspace);
    vec3 albedo = vec3(1, 0, 0);
    float kD = max(0.0, dot(L,N));
    //outColor.rgb = albedo * kD;
    outColor.rgb += albedo * ambientTerm;
    outColor.a = 1.0;

    // Gamma Correction
    outColor.rgb = pow(outColor.rgb, vec3(1.0/2.4));

}
