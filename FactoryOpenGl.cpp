#include "FactoryOpenGl.h"
#include "ShaderOpenGl.h"

IShader* FactoryOpenGl::makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const
{
    return new ShaderOpenGl(vertexFilePath, fragmentFilePath);
}
