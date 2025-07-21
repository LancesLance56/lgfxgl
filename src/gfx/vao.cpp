#include "vao.h"

GLenum catch_error;

VAO vao_create() {
   GLuint id;
   glGenVertexArrays(1, &id);
   const VAO self = {
      .ID = id
   };
   return self;
}

void vao_destroy(const struct VAO self) {
   glDeleteVertexArrays(1, &self.ID);
}

void vao_bind(const struct VAO self) {
   glBindVertexArray(self.ID);
}

void vao_vattribptr(const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const std::size_t offset) {
   glVertexAttribPointer(index, size, type, GL_FALSE, stride, reinterpret_cast<void *>(offset));
   glEnableVertexAttribArray(index);
}

