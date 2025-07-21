#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
};

#define MAX_LIGHTS 4
#define MAX_TERRAIN_TYPES 8

uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform int terrainTypeCount;
uniform float terrainHeights[MAX_TERRAIN_TYPES];
uniform sampler2D terrainTextures[MAX_TERRAIN_TYPES];
uniform vec3 terrainColors[MAX_TERRAIN_TYPES];
uniform Material terrainMaterials[MAX_TERRAIN_TYPES];

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in float WorldHeight;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);

    float heightNormalized = clamp(WorldHeight, 0.0, 1.0);
    vec3 terrainColor = vec3(1.0);
    vec3 texColor = vec3(1.0);
    Material currentMaterial;
    currentMaterial.ambient = vec3(0.0);
    currentMaterial.diffuse = vec3(0.0);
    currentMaterial.specular = vec3(0.0);
    currentMaterial.shininess = 0.0;

    // === Lighting ===
    for (int i = 0; i < lightCount; ++i) {
        for (int i = 0; i < terrainTypeCount; ++i) {
            if (heightNormalized >= terrainHeights[i] && heightNormalized < terrainHeights[i + 1]) {
                currentMaterial = terrainMaterials[i];
                break;
            }
        }

        // Ambient
        vec3 ambient = currentMaterial.ambient * lights[i].color;

        // Diffuse
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = currentMaterial.diffuse * diff * lights[i].color;

        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), currentMaterial.shininess);
        vec3 specular = currentMaterial.specular * spec * lights[i].color;

        result += (ambient + diffuse + specular);
    }

    // === Terrain Blending ===
    if (heightNormalized < terrainHeights[1]) {
        // Blend layer 0 and 1
        float t = smoothstep(terrainHeights[0], terrainHeights[1], heightNormalized);
        vec3 color0 = terrainColors[0];
        vec3 color1 = terrainColors[1];
        vec3 tex0 = texture(terrainTextures[0], TexCoord).rgb;
        vec3 tex1 = texture(terrainTextures[1], TexCoord).rgb;

        terrainColor = mix(color0, color1, t);
        texColor = mix(tex0, tex1, t);
    } else {
        for (int i = 1; i < terrainTypeCount - 1; ++i) {
            if (heightNormalized >= terrainHeights[i] && heightNormalized < terrainHeights[i + 1]) {
                terrainColor = terrainColors[i];
                texColor = texture(terrainTextures[i], TexCoord).rgb;
                break;
            }
        }

        if (heightNormalized >= terrainHeights[terrainTypeCount - 1]) {
            terrainColor = terrainColors[terrainTypeCount - 1];
            texColor = texture(terrainTextures[terrainTypeCount - 1], TexCoord).rgb;
        }
    }

    result *= (terrainColor * 0.8) + (texColor * 0.2);
    FragColor = vec4(result, 1.0);
}
