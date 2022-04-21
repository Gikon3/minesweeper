#pragma once

#include "IShader.h"
#include "ITransformer.h"
#include "IVao.h"

struct IFactory
{
    virtual ~IFactory() = default;
    virtual IShader* makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const = 0;
    virtual ITransformer* makeTransformer() const = 0;
    virtual IVao* makeVao() const = 0;
};
