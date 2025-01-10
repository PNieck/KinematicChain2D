#pragma once

#include <glm/vec2.hpp>


class Rectangle {
public:
    Rectangle(const glm::vec2& lowerLeftCorner, float width, float height);
    Rectangle(const glm::vec2& corner1, const glm::vec2& corner2);

    [[nodiscard]]
    glm::vec2 UpperLeftCorner() const
        { return glm::vec2(lowerLeftCorner.x, lowerLeftCorner.y + height); }

    [[nodiscard]]
    glm::vec2 UpperRightCorner() const
        { return glm::vec2(lowerLeftCorner.x + width, lowerLeftCorner.y + height);  }

    [[nodiscard]]
    glm::vec2 LowerLeftCorner() const
        { return lowerLeftCorner; }

    [[nodiscard]]
    glm::vec2 LowerRightCorner() const
        { return glm::vec2(lowerLeftCorner.x + width, lowerLeftCorner.y); }

private:
    glm::vec2 lowerLeftCorner;
    float width, height;
};
