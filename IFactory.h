#pragma once

#include "IShader.h"
#include "ITransformer.h"

struct IFactory
{
    virtual ~IFactory() = default;
    virtual IShader* makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const = 0;
    virtual ITransformer* makeTransformer() const = 0;
};
