#pragma once

#include <glm/vec2.hpp>


class Rectangle {
public:
    Rectangle() = default;
    Rectangle(const glm::vec2& lowerLeftCorner, float width, float height);
    Rectangle(const glm::vec2& corner1, const glm::vec2& corner2);

    [[nodiscard]]
    glm::vec2 UpperLeftCorner() const
        { return { lowerLeftCorner.x, lowerLeftCorner.y + height }; }

    [[nodiscard]]
    glm::vec2 UpperRightCorner() const
        { return { lowerLeftCorner.x + width, lowerLeftCorner.y + height }; }

    [[nodiscard]]
    glm::vec2 LowerLeftCorner() const
        { return lowerLeftCorner; }

    [[nodiscard]]
    glm::vec2 LowerRightCorner() const
        { return { lowerLeftCorner.x + width, lowerLeftCorner.y }; }

    [[nodiscard]]
    float Width() const
        { return width; }

    [[nodiscard]]
    float Height() const
        { return height; }

private:
    glm::vec2 lowerLeftCorner;
    float width, height;
};
