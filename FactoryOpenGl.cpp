#include "FactoryOpenGl.h"
#include "ShaderOpenGl.h"
#include "TransformerOpenGl.h"

IShader* FactoryOpenGl::makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const
{
    return new ShaderOpenGl(vertexFilePath, fragmentFilePath);
}

ITransformer* FactoryOpenGl::makeTransformer() const
{
    return new TransformerOpenGl();
}
