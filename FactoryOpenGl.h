#pragma once

#include "IFactory.h"

struct FactoryOpenGl : public IFactory
{
    FactoryOpenGl() = default;
    ~FactoryOpenGl() = default;
    IShader* makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath) const override;
};
