#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TransformerOpenGl.h"

void TransformerOpenGl::translate(std::array<float, 3> dimensions)
{
    _matrix = glm::translate(_matrix, glm::vec3(dimensions[0], dimensions[1], dimensions[2]));
}

void TransformerOpenGl::rotate(float angle, std::array<float, 3> axle)
{
    _matrix = glm::rotate(_matrix, angle, glm::vec3(axle[0], axle[1], axle[2]));
}

void TransformerOpenGl::scale(std::array<float, 3> dimensions)
{
    _matrix = glm::scale(_matrix, glm::vec3(dimensions[0], dimensions[1], dimensions[2]));
}

const float* TransformerOpenGl::valuePtr() const
{
    return glm::value_ptr(_matrix);
}
