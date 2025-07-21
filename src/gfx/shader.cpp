#include "shader.h"

#include <format>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

Shader::Shader() = default;

Shader::~Shader() {
    if (ID != 0) {
        glDeleteProgram(ID);
    }
}

Shader::Shader(const std::string &pathToVertexShader, const std::string &pathToFragmentShader) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(pathToVertexShader);
        fShaderFile.open(pathToFragmentShader);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }

    catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        std::cout << pathToVertexShader << " not found in file" << std::endl;
        std::cout << pathToFragmentShader << " not found in file" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    check_shader_compiler_errors(vertexShader, ShaderType::VERTEX_SHADER);
    check_shader_compiler_errors(fragmentShader, ShaderType::FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    check_shader_compiler_errors(ID, ShaderType::SHADER_PROGRAM);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// In shader.cpp
void Shader::check_shader_compiler_errors(const GLuint id, const ShaderType type) {
    int success;
    char infoLog[512];

    switch (type) {
        case ShaderType::VERTEX_SHADER:
        case ShaderType::FRAGMENT_SHADER:
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(id, 512, nullptr, infoLog);
                std::cerr << "Error: " << (type == ShaderType::VERTEX_SHADER ? "Vertex" : "Fragment")
                          << " Shader Compilation Failed\n" << infoLog << std::endl;
            } else {
                // Always print info log, even on success, for warnings
                glGetShaderInfoLog(id, 512, nullptr, infoLog);
                if (strlen(infoLog) > 0) {
                    std::cout << "Info/Warning for " << (type == ShaderType::VERTEX_SHADER ? "Vertex" : "Fragment")
                              << " Shader:\n" << infoLog << std::endl;
                }
            }
            break;

        case ShaderType::SHADER_PROGRAM:
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(id, 512, nullptr, infoLog);
                std::cerr << "Error: Shader Program Linking Failed\n" << infoLog << std::endl;
            } else {
                // Always print info log, even on success, for warnings
                glGetProgramInfoLog(id, 512, nullptr, infoLog);
                if (strlen(infoLog) > 0) {
                    std::cout << "Info/Warning for Shader Program:\n" << infoLog << std::endl;
                }
            }
            break;
    }
}


void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setFloatArray(const std::string& name, const std::vector<float>& values) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1fv(location, values.size(), values.data());
    } else {
        std::cerr << "Warning: Float array uniform '" << name << "' not found.\n";
    }
}

void Shader::setVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform3fv(location, values.size(), glm::value_ptr(values[0]));
    } else {
        std::cerr << "Warning: Vec3 array uniform '" << name << "' not found.\n";
    }
}

void Shader::setMaterialArray(const std::string &name, const std::vector<Material> &values) const {
    GLint location = glGetUniformLocation(ID, (std::format("{}[{}]{}", name, 0, ".ambient").c_str()));
    if (location != -1) {
        for (int i = 0; i < values.size(); ++i) {
            auto variable_name = std::format("{}[{}]", name, i); // "<name>[i]"
            glUniform3fv(glGetUniformLocation(ID, (variable_name + ".ambient").c_str()), 1, &values[i].ambient[0]);
            glUniform3fv(glGetUniformLocation(ID, (variable_name + ".diffuse").c_str()), 1, &values[i].diffuse[0]);
            glUniform3fv(glGetUniformLocation(ID, (variable_name + ".specular").c_str()), 1, &values[i].specular[0]);
            glUniform1f(glGetUniformLocation(ID, (variable_name + ".shininess").c_str()), values[i].shininess);
        }
    } else {
        std::cerr << "Warning: Material array uniform '" << name << "' not found.\n";
    }
}



void Shader::use() const {
    if (ID == 0) {
        std::cerr << "[WARN] Tried to use shader program before initialization.\n";
        return;
    }
    glUseProgram(ID);
}

