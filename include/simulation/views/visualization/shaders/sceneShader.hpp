#pragma once

#include "shader.hpp"

#include "../../../model/coordinateSystem.hpp"


class SceneShader: public Shader {
public:
    SceneShader():
        Shader(
            "../../shaders/sceneShader.vert",
            "../../shaders/flatColorShader.frag"
        ) {}

    void SetColor(const glm::vec4& color) const
        { SetVec4("color", color); }

    void SetColor(const float r, const float g, const float b) const
        { SetVec4("color", r, g, b, 1.f); }

    void SetCoordinateSystem(const CoordinateSystem& coordinateSystem) const
        { SetVec2("maxCoordinates", coordinateSystem.maxX, coordinateSystem.maxY); }
};
