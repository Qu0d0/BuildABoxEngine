//
// Created by Oddball on 30/10/2022.
//
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include "engine/assetLoader/Assets.h"
#include "engine/renderer/rendererComponents/ShaderComponent.h"


unsigned int ShaderComponent::s_fragmentShader = 0;
unsigned int ShaderComponent::s_vertexShader = 0;

struct glStatusData {
    int success;
    const char *shaderName;
    char infoLog[GL_INFO_LOG_LENGTH];
};


unsigned int ShaderComponent::loadAndCompileShader(GLuint shaderType, const fs::path &shaderPath) {
    auto shaderSource = readText(shaderPath);
    auto source = shaderSource.c_str();
    auto shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    glStatusData compilationStatus{};
    compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
    if(compilationStatus.success == GL_FALSE) {
        glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
        throw std::runtime_error("ERROR: " + std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
                                 std::string(compilationStatus.infoLog));
    }

    return shaderID;
}

void ShaderComponent::use() const {
    glUseProgram(shaderProgram);
}

void ShaderComponent::setMatrix(const std::string &uniformName, glm::mat4 matrix) const {
    auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderComponent::setVector(const std::string &uniformName, glm::vec4 vector) const {
    auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
}

void ShaderComponent::setTextrue(const std::string &uniformName) const {
    //auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    auto uniformLocation = glGetUniformLocation(shaderProgram, "tex0");
    //GLuint tex0Uni = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1i(uniformLocation, 0);
}

std::string ShaderComponent::readText(const fs::path &filePath) {
    std::ifstream sourceFile(resolveAssetPath(filePath));
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    return buffer.str();
}


