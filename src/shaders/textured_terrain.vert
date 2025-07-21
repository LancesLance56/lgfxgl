#version 330 core

#define MAX_REMAP_RESOLUTION 10
#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormal;

uniform mat4 mvp;
uniform mat4 model;

// Bezier LUT
uniform float heightRemapLUT[MAX_REMAP_RESOLUTION];
uniform int remapResolution;

// Terrain world height bounds
uniform float heightMin = FLT_MIN;
uniform float heightMax = FLT_MAX;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out float WorldHeight; // Output world-space y for fragment use

float remapHeight(float h) {
    float clamped = clamp(h, 0.0, 1.0);
    float scaled = clamped * float(remapResolution - 1);
    int index = int(scaled);
    int nextIndex = min(index + 1, remapResolution - 1);
    float fraction = scaled - float(index);
    return mix(heightRemapLUT[index], heightRemapLUT[nextIndex], fraction);
}

void main() {
    float rawHeight = inPosition.y;
    float normalizedHeight = clamp((rawHeight - heightMin) / (heightMax - heightMin), 0.0, 1.0);
    float remapped = remapHeight(normalizedHeight);
    float displacedY = remapped * (heightMax - heightMin) + heightMin;

    vec3 pos = vec3(inPosition.x, displacedY, inPosition.z);

    FragPos = vec3(model * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * inNormal;
    TexCoord = inTexCoord;
    WorldHeight = displacedY;
    gl_Position = mvp * vec4(pos, 1.0);
}
