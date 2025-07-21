#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>

class Material {
public:
    glm::vec3 ambient;   // Usually small, e.g., 0.1 * base color
    glm::vec3 diffuse;   // Base color
    glm::vec3 specular;  // White or base color
    float shininess;     // 32.0, 64.0, 128.0...

    Material();
    Material(const glm::vec3 &ambient,
             const glm::vec3 &diffuse,
             const glm::vec3 &specular,
             float shininess);

    void applyToShader(const class Shader &shader, const std::string &prefix = "material") const;
};





#endif //MATERIAL_H
