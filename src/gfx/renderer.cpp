#include "renderer.h"
#include "lightpos.h"

Renderer::Renderer() = default;

// no texture
Renderer::Renderer(
        std::shared_ptr<Shader> shader, const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices,
        const GLsizei sizeOfVertices, const GLsizei sizeOfIndices, const glm::vec3 rgb) :
    vao(vao_create()), vbo(abo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW)),
    ebo(abo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)), shouldDrawElements(true), count(sizeOfIndices),
    texture(UNDEFINED_TEXTURE_LOCATION), m_model(glm::mat4(1.0f)), mvp(glm::mat4(1.0f)), shader(shader) {

    vao_bind(vao);

    abo_data(vbo, sizeOfVertices * sizeof(float), vertices);
    abo_data(ebo, sizeOfIndices * sizeof(unsigned int), indices);

    shader->use();
    shader->setVec3("color", rgb);

    vao_vattribptr(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
}

Renderer::Renderer(
        std::shared_ptr<Shader> shader, const std::string &pathToImage, const std::vector<GLfloat> &vertices,
        const std::vector<GLuint> &indices, GLsizei sizeOfVertices, GLsizei sizeOfIndices) :
    vao(vao_create()), vbo(abo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW)),
    ebo(abo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)), shouldDrawElements(true), count(sizeOfIndices),
    m_model(glm::mat4(1.0f)), mvp(glm::mat4(1.0f)), shader(shader) {
    vao_bind(vao);

    abo_data(vbo, sizeOfVertices * sizeof(float), vertices);
    abo_data(ebo, sizeOfIndices * sizeof(unsigned int), indices);

    vao_vattribptr(0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao_vattribptr(1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    glUseProgram(shader->ID);
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "mvp"), 1, GL_FALSE, &mvp[0][0]);

    if (pathToImage.empty()) {
        texture = UNDEFINED_TEXTURE_LOCATION;
        return;
    }

    texture = create_opengl_texture(pathToImage, shader->ID);
    if (texture == 0) {
        std::cout << "create_opengl_texture failed" << std::endl;
    }
}

Renderer::Renderer(
        std::shared_ptr<Shader> shader, const std::string &pathToImage, const std::vector<GLfloat> &vertices,
        const std::vector<GLuint> &indices, GLsizei sizeOfVertices, GLsizei sizeOfIndices, const glm::mat4 &model) :
    shouldDrawElements(true), shouldDrawNormals(true), count(sizeOfIndices), texture(UNDEFINED_TEXTURE_LOCATION),
    m_model(glm::mat4(1.0f)), mvp(glm::mat4(1.0f)), shader(shader) {
    vao = vao_create();
    vbo = abo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    ebo = abo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    vao_bind(vao);

    abo_data(vbo, sizeOfVertices * sizeof(float), vertices);
    abo_data(ebo, sizeOfIndices * sizeof(unsigned int), indices);

    vao_vattribptr(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao_vattribptr(1, 2, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
    vao_vattribptr(2, 3, GL_FLOAT, 8 * sizeof(float), 5 * sizeof(float));

    glUseProgram(shader->ID);
    shader->setInt("lightCount", global_lights.size());

    for (int i = 0; i < global_lights.size(); ++i) {
        shader->setVec3("lights[" + std::to_string(i) + "].position", global_lights[i].position);
        shader->setVec3("lights[" + std::to_string(i) + "].color", global_lights[i].color);
    }

    shader->setMat4("model", m_model);
    shader->setMat4("mvp", mvp);

    if (pathToImage.empty()) {
        texture = UNDEFINED_TEXTURE_LOCATION;
        return;
    }
    texture = create_opengl_texture(pathToImage, shader->ID);
    if (texture == 0)
        std::cout << "[Renderer.cpp] create_opengl_texture failed" << std::endl;
}

void Renderer::draw(const glm::mat4 &mvp, const Camera &camera) const {
    shader->use();
    shader->setMat4("mvp", mvp);
    shader->setVec3("viewPos", camera.position);
    vao_bind(vao);
    if (shouldDrawNormals) {
        for (int i = 0; i < global_lights.size(); ++i) {
            shader->setVec3("lights[" + std::to_string(i) + "].position", global_lights[i].position);
            shader->setVec3("lights[" + std::to_string(i) + "].color", global_lights[i].color);
        }

        if (texture != 0 && texture != UNDEFINED_TEXTURE_LOCATION) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    } else if (texture != UNDEFINED_TEXTURE_LOCATION) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}
