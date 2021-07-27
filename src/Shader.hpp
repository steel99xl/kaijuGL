#pragma once

#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include "Engine.hpp"

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;

};

class Shader{
private:
    std::string m_FilePath;
    unsigned int m_RenderID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;


public:
    Shader();
    ~Shader();

    void SetShader(const std::string &filePath);

    void Bind() const;
    void UnBind();

    // Set Uniforms
    void SetUniform1i(const std::string &name, int value);
    void SetUniform1iv(const std::string &name, GLsizei size, const GLint *array);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

    int GetUniformLocation(const std::string &name) const ;
    inline int GetRenderID() const {return m_RenderID;};

private:
    ShaderProgramSource ParseShader();
    unsigned int CreateShader(std::string &vertexShader, std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, std::string &source);

};



