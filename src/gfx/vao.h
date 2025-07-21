#ifndef VAO_H
#define VAO_H

#include "glad_include.h"
#include <iostream>

struct VAO {
    GLuint ID;
};

VAO vao_create();
void vao_destroy(VAO self);
void vao_bind(VAO self);
void vao_vattribptr(GLuint index, GLint size, GLenum type, GLsizei stride, std::size_t offset);

#endif
