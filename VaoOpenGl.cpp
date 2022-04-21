#include <glad/glad.h>
#include "VaoOpenGl.h"

VaoOpenGl::VaoOpenGl()
{
    glGenVertexArrays(1, &_vao);
}

void VaoOpenGl::addVertices(const std::vector<float>& vertices)
{
    _size = vertices.size();

    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VaoOpenGl::addIndices(const std::vector<unsigned int>& indices)
{
    _drawType = DrawType::ELEMENTS;
    _size = indices.size();

    glGenBuffers(1, &_ebo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VaoOpenGl::setAttribute(unsigned int index, unsigned int size, unsigned int stride, unsigned int start) const
{
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(start * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VaoOpenGl::draw() const
{
    glBindVertexArray(_vao);
    switch (_drawType) {
        case DrawType::ARRAYS:
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_size));
            break;
        case DrawType::ELEMENTS:
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_size), GL_UNSIGNED_INT, 0);
            break;
    }
    glBindVertexArray(0);
}
