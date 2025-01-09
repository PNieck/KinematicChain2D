#pragma once

#include "shader.hpp"


class StdShader: public Shader {
public:
    StdShader():
        Shader(
            "../../shaders/passThroughShader.vert",
            "../../shaders/flatColorShader.frag"
        ) {}

    void SetColor(const glm::vec4& color) const
        { SetVec4("color", color); }

    void SetColor(const float r, const float g, const float b) const
        { SetVec4("color", r, g, b, 1.f); }
};
