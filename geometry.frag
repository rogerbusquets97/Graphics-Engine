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
uniform sampler2D heightMap;
uniform mat4 modelMatrix;
uniform int diffuseEnabled;
uniform int normalEnabled;
uniform int parallaxEnabled;
uniform vec3 lightPos;
uniform vec3 viewPos;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy * 0.1;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(heightMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(heightMap, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(heightMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}


void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = FSIn.positionViewspace;
    // also store the per-fragment normals into the gbuffer
    vec2 TexCoords = FSIn.texCoords;

    if(normalEnabled == 1)
    {
        vec3 T = normalize(FSIn.tangentLocalspace);
        vec3 B = normalize(FSIn.bitangentLocalspace);
        vec3 N = normalize(FSIn.normalLocalspace);

        mat3 TBN = mat3(T, B, N);

        if(parallaxEnabled == 1)
        {
            vec3 TangentLightPos = TBN * lightPos;
            vec3 TangentViewPos = TBN * viewPos;
            vec3 TangentFragPos = TBN * FSIn.positionViewspace;

            vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
            TexCoords = ParallaxMapping(TexCoords, viewDir);
        }

        vec3 normalTangent = texture(normalMap, TexCoords).rgb;
        normalTangent = normalize(normalTangent * 2.0 - 1.0);

        vec3 normalLocal = normalize(TBN * normalTangent);
        vec3 normalView = normalize(modelMatrix * vec4(normalLocal, 0.0)).xyz;

        gNormal = normalView;
    }
    else
    {
        gNormal = normalize(FSIn.normalViewspace);
    }

    if(diffuseEnabled == 1)
    {
        gAlbedo.rgb = texture(diffuseTexture, TexCoords).rgb;
    }
    else
    {
        gAlbedo.rgb = vec3(1.0);
    }
    // and the diffuse per-fragment color

}
