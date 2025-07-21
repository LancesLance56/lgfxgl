#ifndef CUBE_H
#define CUBE_H

#include <memory>


#include "mesh.h"

extern std::vector<GLfloat> vertices;
extern std::vector<GLuint> indices;

class Cube {
public:
    glm::mat4 model;
    Mesh<MeshType::COLOR> cubeMesh;
    float size = 0.0f;

    static std::shared_ptr<Shader> shaderProgram;
    Cube(glm::vec3 position, glm::vec3 rotation, float size, glm::vec3 rgb, std::string texturePath = ""); // not sdt::string& fix later
    void draw(const glm::mat4 &mvp, const Camera &camera) const;
};

#endif
