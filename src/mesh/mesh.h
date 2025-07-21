#ifndef MESH_H
#define MESH_H

#include <memory>


#include <glm/glm.hpp>
#include "gfx.h"

#include "renderer.h"

enum class MeshType {
    COLOR,
    COLOR_TEXTURE,
    COLOR_TEXTURE_NORMALS,
    COLOR_NORMALS
};

template<MeshType T>
class Mesh {
public:
    Renderer renderer;
    std::vector<GLuint> indices;
    std::vector<GLfloat> vertices;
    GLsizei sizeOfIndices;
    GLsizei sizeOfVertices;
    glm::vec3 rgb;
    GLuint texture;

    Mesh() = default;

    explicit Mesh(
            const std::shared_ptr<Shader> &shader,
        const std::string &texturePath,
        const std::vector<GLuint> &indices,
        const std::vector<GLfloat> &vertices,
        GLsizei sizeOfIndices = 0,
        GLsizei sizeOfVertices = 0,
        glm::vec3 rgb = glm::vec3(1.0f),
        const glm::mat4 &m_model = glm::mat4(1.0f)
    );
};


#endif
