#pragma once

#include <glm/glm.hpp>
#include "ITransformer.h"

class TransformerOpenGl final : public ITransformer
{
public:
    TransformerOpenGl() = default;
    ~TransformerOpenGl() = default;
    void translate(std::array<float, 3> dimensions) override;
    void rotate(float angle, std::array<float, 3> axle) override;
    void scale(std::array<float, 3> dimensions) override;
    const float* valuePtr() const override;

private:
    glm::mat4 _matrix;
};
