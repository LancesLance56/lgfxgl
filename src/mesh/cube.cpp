#include "cube.h"

std::vector<GLfloat> vertices = {
        // Front face
        -0.5f, -0.5f, 0.5f, // 0
        0.5f, -0.5f, 0.5f, // 1
        0.5f, 0.5f, 0.5f, // 2
        -0.5f, 0.5f, 0.5f, // 3

        // Back face
        -0.5f, -0.5f, -0.5f, // 4
        0.5f, -0.5f, -0.5f, // 5
        0.5f, 0.5f, -0.5f, // 6
        -0.5f, 0.5f, -0.5f // 7
};

std::vector<GLuint> indices = {
        // Front face (CCW when looking at front)
        0, 2, 1, 0, 3, 2,

        // Right face
        1, 6, 5, 1, 2, 6,

        // Back face
        5, 7, 4, 5, 6, 7,

        // Left face
        4, 3, 0, 4, 7, 3,

        // Bottom face
        4, 1, 5, 4, 0, 1,

        // Top face
        3, 6, 2, 3, 7, 6};

std::shared_ptr<Shader> Cube::shaderProgram;

Cube::Cube(const glm::vec3 position, const glm::vec3 rotation, const float size, const glm::vec3 rgb, std::string texturePath) :
    cubeMesh() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(size, size, size));
    shaderProgram = std::make_shared<Shader>("./src/shaders/color.vert", "./src/shaders/color.frag");
    cubeMesh = Mesh<MeshType::COLOR>(shaderProgram, "", indices, vertices, 36, 36);
}

void Cube::draw(const glm::mat4 &mvp, const Camera &camera) const { cubeMesh.renderer.draw(mvp * model, camera); }
