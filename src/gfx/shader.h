#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "glad/glad.h"

#include "material.h"

enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, SHADER_PROGRAM };


class Shader {

public:
    GLuint ID;

    Shader();
    ~Shader(); // Add this inside the class definition
    Shader(const std::string &pathToVertexShader, const std::string &pathToFragmentShader);
    static void check_shader_compiler_errors(GLuint shaderID, ShaderType shaderType);

    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setFloatArray(const std::string& name, const std::vector<float>& values) const;
    void setVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const;
    void setMaterialArray(const std::string& name, const std::vector<Material>& values) const;
    void use() const;
};

#endif
