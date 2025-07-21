#ifndef RENDERER_H
#define RENDERER_H

#include "vao.h"
#include "abo.h"
#include "shader.h"

#include "texture.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

class Renderer {
    struct VAO vao{};
    struct ABO vbo{};
    struct ABO ebo{};

    bool shouldDrawElements = false; // glDrawArrays or glDrawElements
    bool shouldDrawNormals = false;

    GLuint UNDEFINED_TEXTURE_LOCATION = 180;
    GLuint count{};
    GLuint texture = UNDEFINED_TEXTURE_LOCATION;


public:
    glm::mat4 m_model;
    glm::mat4 mvp; // WARNING: MVP IS NOT INITIALIZED IN THE CONSTRUCTOR AND IS ONLY INITIALIZED IN THE DRAW FUNCTION
    std::shared_ptr<Shader> shader;

    Renderer();
    Renderer(std::shared_ptr<Shader> shader, const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices, GLsizei sizeOfVertices, GLsizei sizeOfIndices, glm::vec3 rgb); // no texture
    Renderer(std::shared_ptr<Shader> shader, const std::string &pathToImage, const std::vector<GLfloat> &vertices,
            const std::vector<GLuint> &indices,
        GLsizei sizeOfVertices, GLsizei sizeOfIndices); // with texture
    Renderer(std::shared_ptr<Shader> shader, const std::string &pathToImage, const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices,
        GLsizei sizeOfVertices, GLsizei sizeOfIndices, const glm::mat4 &model); // with heightmap

    void draw(const glm::mat4 &mvp, const Camera &camera) const;
    void set_polygon_mode(GLenum mode);

};

#endif
