#pragma once

#include <GLFW/glfw3.h>
#include "IVao.h"

class VaoOpenGl final : public IVao
{
public:
    VaoOpenGl();
    ~VaoOpenGl() = default;
    void addVertices(const std::vector<float>&vertices) override;
    void addIndices(const std::vector<unsigned int>&indices) override;
    void setAttribute(unsigned int index, unsigned int size, unsigned int stride, unsigned int start) const override;
    void draw() const override;

private:
    enum class DrawType { ARRAYS, ELEMENTS };

private:
    GLuint _vao = 0;
    GLuint _ebo = 0;
    GLuint _vbo = 0;
    size_t _size = 0;
    DrawType _drawType = DrawType::ARRAYS;
};
