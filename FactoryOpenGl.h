#pragma once

#include "IFactory.h"

struct FactoryOpenGl final : public IFactory
{
    FactoryOpenGl() = default;
    ~FactoryOpenGl() = default;
    IShader* makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const override;
    ITransformer* makeTransformer() const override;
    IVao* makeVao() const override;
};
