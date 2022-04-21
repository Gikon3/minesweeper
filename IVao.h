#pragma once

#include <vector>

struct IVao
{
    virtual ~IVao() = default;
    virtual void addVertices(const std::vector<float>& vertices) = 0;
    virtual void addIndices(const std::vector<unsigned int>& indices) = 0;
    virtual void setAttribute(unsigned int index, unsigned int size, unsigned int stride, unsigned int start) const = 0;
    virtual void draw() const = 0;
};
