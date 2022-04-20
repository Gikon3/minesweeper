#pragma once

#include <array>

struct ITransformer
{
    virtual ~ITransformer() = default;
    virtual void translate(std::array<float, 3> dimensions) = 0;
    virtual void rotate(float angle, std::array<float, 3> axle) = 0;
    virtual void scale(std::array<float, 3> dimensions) = 0;
    virtual const float* valuePtr() const = 0;
};
