#include "mesh.h"

#include <utility>

template<>
Mesh<MeshType::COLOR>::Mesh(
        const std::shared_ptr<Shader> &shader, const std::string &texturePath,
        const std::vector<GLuint> &indices, const std::vector<GLfloat> &vertices,
        const GLsizei sizeOfIndices,
        const GLsizei sizeOfVertices, const glm::vec3 rgb,
        const glm::mat4 &m_model) :
    indices(indices), vertices(vertices),
    sizeOfIndices(sizeOfIndices),
    sizeOfVertices(sizeOfVertices), rgb(rgb), texture(0) {
    renderer = Renderer(
            shader, vertices, indices, sizeOfIndices,
            sizeOfVertices, rgb);
}

template<>
Mesh<MeshType::COLOR_TEXTURE>::Mesh(
        const std::shared_ptr<Shader> &shader, const std::string &texturePath,
        const std::vector<GLuint> &indices, const std::vector<GLfloat> &vertices,
        const GLsizei sizeOfIndices,
        const GLsizei sizeOfVertices, const glm::vec3 rgb,
        const glm::mat4 &m_model) :
    indices(indices), vertices(vertices),
    sizeOfIndices(sizeOfIndices),
    sizeOfVertices(sizeOfVertices), rgb(rgb), texture(0) {
    renderer = Renderer(
            shader, vertices, indices, sizeOfIndices,
            sizeOfVertices, rgb);
}

template<>
Mesh<MeshType::COLOR_TEXTURE_NORMALS>::Mesh(
        const std::shared_ptr<Shader> &shader, const std::string &texturePath,
        const std::vector<GLuint> &indices, const std::vector<GLfloat> &vertices,
        const GLsizei sizeOfIndices,
        const GLsizei sizeOfVertices, const glm::vec3 rgb,
        const glm::mat4 &m_model) :
    indices(indices), vertices(vertices),
    sizeOfIndices(sizeOfIndices),
    sizeOfVertices(sizeOfVertices), rgb(rgb), texture(0) {
    renderer = Renderer(
            shader, texturePath, vertices, indices,
            sizeOfIndices, sizeOfVertices, m_model);
}

// COLOR_NORMALS (uses only rgb)
template<>
Mesh<MeshType::COLOR_NORMALS>::Mesh(
        const std::shared_ptr<Shader> &shader, const std::string &texturePath,
        const std::vector<GLuint> &indices, const std::vector<GLfloat> &vertices,
        const GLsizei sizeOfIndices,
        const GLsizei sizeOfVertices, const glm::vec3 rgb,
        const glm::mat4 &m_model) :
    indices(indices), vertices(vertices),
    sizeOfIndices(sizeOfIndices),
    sizeOfVertices(sizeOfVertices), rgb(rgb), texture(0) {
    renderer = Renderer(
            shader, texturePath, vertices, indices,
            sizeOfIndices, sizeOfVertices, m_model);
}
