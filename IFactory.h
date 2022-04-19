#pragma once

#include "IShader.h"

struct IFactory
{
    virtual ~IFactory() = default;
    virtual IShader* makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const = 0;
};
