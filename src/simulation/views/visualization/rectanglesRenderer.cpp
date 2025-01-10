#include <simulation/views/visualization/rectanglesRenderer.hpp>

#include <stdexcept>


void RectanglesRenderer::AddRectangle(const Rectangle &rectangle)
{
    vertices.reserve(vertices.size() + 4);

    vertices.push_back(rectangle.LowerLeftCorner());
    vertices.push_back(rectangle.UpperLeftCorner());
    vertices.push_back(rectangle.UpperRightCorner());
    vertices.push_back(rectangle.LowerRightCorner());

    indices.reserve(indices.size() + 6);

    // First triangle
    indices.push_back(nextHighestIndex++);
    indices.push_back(nextHighestIndex++);
    indices.push_back(nextHighestIndex++);

    // Second triangle
    indices.push_back(nextHighestIndex-1);
    indices.push_back(nextHighestIndex++);
    indices.push_back(nextHighestIndex-4);

    mesh.Update(vertices, indices);
}

void RectanglesRenderer::EditRectangle(const Rectangle &oldRectangle, const Rectangle &newRectangle)
{
    const auto optIndex = FindTriangle(oldRectangle);
    if (!optIndex.has_value())
        throw std::runtime_error("Could not find triangle");

    const size_t index = optIndex.value();

    vertices[index] = newRectangle.LowerLeftCorner();
    vertices[index + 1] = newRectangle.UpperLeftCorner();
    vertices[index + 2] = newRectangle.UpperRightCorner();
    vertices[index + 3] = newRectangle.LowerRightCorner();

    mesh.UpdateSomeVertices(vertices, index, 4);
}


void RectanglesRenderer::Render(const SceneShader &shader) const
{
    shader.SetColor(1.f, 0.f, 0.f);
    mesh.Use();
    glDrawElements(mesh.GetType(), static_cast<GLsizei>(mesh.GetElementsCnt()), GL_UNSIGNED_INT, nullptr);
}


std::optional<size_t> RectanglesRenderer::FindTriangle(const Rectangle &rectangle) const
{
    for (int i = vertices.size() - 4; i >= 0; i -= 4) {
        if (rectangle.LowerLeftCorner() == vertices[i].position &&
            rectangle.UpperLeftCorner() == vertices[i + 1].position &&
            rectangle.UpperRightCorner() == vertices[i + 2].position &&
            rectangle.LowerRightCorner() == vertices[i + 3].position
        )   return i;
    }

    return std::nullopt;
}
