#pragma once

#include "mesh.hpp"
#include "vertex.hpp"
#include "simulation/model/rectangle.hpp"

#include <optional>

#include "shaders/sceneShader.hpp"


class RectanglesRenderer {
public:
    void AddRectangle(const Rectangle& rectangle);

    void EditRectangle(const Rectangle& oldRectangle, const Rectangle& newRectangle);

    void Render(const SceneShader& shader) const;
private:
    std::vector<Vertex2D> vertices;
    std::vector<uint32_t> indices;
    uint32_t nextHighestIndex = 0;

    Mesh mesh;

    std::optional<size_t> FindTriangle(const Rectangle& rectangle) const;
};
