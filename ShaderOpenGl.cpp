#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ShaderOpenGl.h"

ShaderOpenGl::ShaderOpenGl(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
    std::string vertexSource;
    std::string fragmentSource;

    struct SourceItem
    {
        const std::string&  name;
        std::string&        source;
    };
    std::vector<SourceItem> sourceItems;
    sourceItems.push_back({ vertexFilePath, vertexSource });
    sourceItems.push_back({ fragmentFilePath, fragmentSource });

    try {
        for (SourceItem& item : sourceItems) {
            std::ifstream file(item.name);
            std::stringstream fileStream;
            fileStream << file.rdbuf();
            file.close();
            item.source = fileStream.str();
        }
    }
    catch (std::ifstream::failure e) {
        std::cout << "Error::Shader::FileNotSuccesfullyRead" << std::endl;
        throw;
    }

    ShaderUnit vertex = createShader(vertexSource, ShaderType::VERTEX);
    compileShader(vertex);
    ShaderUnit fragment = createShader(fragmentSource, ShaderType::FRAGMENT);
    compileShader(fragment);
    linkProgram(vertex, fragment);
}

void ShaderOpenGl::setUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void ShaderOpenGl::setUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void ShaderOpenGl::setUniform(const std::string& name, int value0, int value1, int value2, int value3) const
{
    glUniform4i(glGetUniformLocation(_program, name.c_str()), value0, value1, value2, value3);
}

void ShaderOpenGl::setUniform(const std::string& name, float value0, float value1, float value2, float value3) const
{
    glUniform4f(glGetUniformLocation(_program, name.c_str()), value0, value1, value2, value3);
}

void ShaderOpenGl::setUniform(const std::string& name, const ITransformer* transformer) const
{
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, transformer->valuePtr());
}

void ShaderOpenGl::use() const
{
    glUseProgram(_program);
}

ShaderOpenGl::ShaderUnit ShaderOpenGl::createShader(const std::string& source, ShaderOpenGl::ShaderType type) const
{
    const char* rawStr = source.c_str();
    GLuint id = glCreateShader(type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &rawStr, nullptr);
    glCompileShader(id);
    return { .type = type, .id = id };
}

void ShaderOpenGl::compileShader(ShaderUnit& unit) const
{
    GLint success;
    glGetShaderiv(unit.id, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(unit.id, sizeof(infoLog), nullptr, infoLog);
        std::cout << "Error::Shader::" << (unit.type == ShaderType::VERTEX ? "Vertex" : "Fragment") <<
            "CompilationFailed" << std::endl << infoLog << std::endl;
    }
}

void ShaderOpenGl::linkProgram(ShaderUnit& shaderA, ShaderUnit& shaderB)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, shaderA.id);
    glAttachShader(program, shaderB.id);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cout << "Error::Shader::Program::LinkingFailed" << std::endl << infoLog << std::endl;
    }
    glDeleteShader(shaderA.id);
    glDeleteShader(shaderB.id);

    _program = program;
}
