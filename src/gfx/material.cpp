#include "material.h"
#include "shader.h"

Material::Material()
    : ambient(0.1f), diffuse(1.0f), specular(1.0f), shininess(32.0f) {}

Material::Material(const glm::vec3 &ambient,
                   const glm::vec3 &diffuse,
                   const glm::vec3 &specular,
                   const float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

void Material::applyToShader(const Shader &shader, const std::string &prefix) const {
    shader.setVec3(prefix + ".ambient", ambient);
    shader.setVec3(prefix + ".diffuse", diffuse);
    shader.setVec3(prefix + ".specular", specular);
    shader.setFloat(prefix + ".shininess", shininess);
}
