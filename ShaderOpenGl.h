#pragma once

#include <glad/glad.h>
#include "IShader.h"

class ShaderOpenGl : public IShader
{
public:
    ShaderOpenGl() = delete;
    ShaderOpenGl(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ~ShaderOpenGl() = default;
    void addUniform(const std::string& name, int value) const override;
    void addUniform(const std::string& name, float value) const override;
    void addUniform(const std::string& name, int value0, int value1, int value2, int value3) const override;
    void addUniform(const std::string& name, float value0, float value1, float value2, float value3) const override;
    void use() const override;

private:
    enum class ShaderType { VERTEX, FRAGMENT };
    struct ShaderUnit
    {
        ShaderType  type;
        GLuint      id;
    };

private:
    ShaderUnit createShader(const std::string& source, ShaderType type) const;
    void compileShader(ShaderUnit& unit) const;
    void linkProgram(ShaderUnit& shaderA, ShaderUnit& shaderB);

private:
    GLuint _program = 0;
};
