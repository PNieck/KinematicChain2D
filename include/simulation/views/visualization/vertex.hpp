#pragma once

#include <glm/vec2.hpp>

#include <glad/glad.h>


template <typename T>
concept Vertex = requires(T t) {
    { T::SetupAttributes() };
};


class Vertex2D {
public:
    Vertex2D() = default;

    Vertex2D(const glm::vec2& pos):
        position(pos) {}

    Vertex2D(const float x, const float y):
        position(x, y) {}

    glm::vec2 position;

    static void SetupAttributes() {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(0));
    }
};
