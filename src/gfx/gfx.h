#ifndef GFX_H
#define GFX_H

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#include "material.h"

// values from 0 to 1
struct Color {
    float red;
    float green;
    float blue;
    float alpha = 1.0f;
};

const Color SKY_BLUE = { 0.529, 0.808, 0.922 };

const Material grassMaterial = Material(
    glm::vec3(0.05f, 0.2f, 0.05f),   // ambient
    glm::vec3(0.1f, 0.6f, 0.1f),    // diffuse
    glm::vec3(0.05f, 0.3f, 0.05f),  // specular
    16.0f                           // shininess
);

const Material dirtMaterial = Material(
    glm::vec3(0.15f, 0.1f, 0.05f),
    glm::vec3(0.4f, 0.3f, 0.2f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    8.0f
);

const Material rockMaterial = Material(
    glm::vec3(0.2f, 0.2f, 0.2f),
    glm::vec3(0.4f, 0.4f, 0.4f),
    glm::vec3(0.3f, 0.3f, 0.3f),
    32.0f
);

const Material snowMaterial = Material(
    glm::vec3(0.8f, 0.8f, 0.8f),
    glm::vec3(0.95f, 0.95f, 0.95f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    64.0f
);

const Material waterMaterial = Material(
    glm::vec3(0.0f, 0.05f, 0.1f),
    glm::vec3(0.0f, 0.3f, 0.6f),
    glm::vec3(0.2f, 0.4f, 0.7f),
    128.0f
);

const Material sandMaterial = Material(
    glm::vec3(0.76f, 0.70f, 0.50f),  // ambient (soft yellowish-tan)
    glm::vec3(0.94f, 0.86f, 0.63f),  // diffuse (brighter sandy color)
    glm::vec3(0.20f, 0.20f, 0.15f),  // specular (low shine, slightly earthy)
    8.0f                             // shininess (low reflectivity)
);


#endif
