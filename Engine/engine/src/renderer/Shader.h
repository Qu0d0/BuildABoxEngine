#pragma once

#include <string>
#include <filesystem>
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace fs = std::filesystem;

namespace gl3 {
    class Shader {
    public:
        Shader(const fs::path &vertexShaderPath, const fs::path &fragmentShaderPath);
        virtual ~Shader();

        // Delete copy constructor
        Shader(const Shader &shader) = delete;

        // Explicit move constructor
        Shader(Shader &&other) noexcept {
            std::swap(this->shaderProgram, other.shaderProgram);
            std::swap(this->vertexShader, other.vertexShader);
            std::swap(this->fragmentShader, other.fragmentShader);
        }

        void setMatrix(const std::string &uniformName, glm::mat4 matrix) const;
        void setVector(const std::string &uniformName, glm::vec4 vector) const;
        void use() const;

    private:
        unsigned int loadAndCompileShader(GLuint shaderType, const fs::path &shaderPath);
        std::string readText(const fs::path &filePath);

        unsigned int shaderProgram = 0;
        unsigned int vertexShader = 0;
        unsigned int fragmentShader = 0;
    };
}


