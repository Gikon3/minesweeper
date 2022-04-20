#pragma once

#include <vector>
#include <string>
#include "ITransformer.h"

class IShader
{
public:
    virtual ~IShader() = default;
    virtual void setUniform(const std::string& name, int value) const = 0;
    virtual void setUniform(const std::string& name, float value) const = 0;
    virtual void setUniform(const std::string& name, int value0, int value1, int value2, int value3) const = 0;
    virtual void setUniform(const std::string& name, float value0, float value1, float value2, float value3) const = 0;
    virtual void setUniform(const std::string& name, const ITransformer* transformer) const = 0;
    virtual void use() const = 0;
};
