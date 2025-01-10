#include <algorithm>
#include <simulation/model/rectangle.hpp>


Rectangle::Rectangle(const glm::vec2 &lowerLeftCorner, const float width, const float height):
    lowerLeftCorner(lowerLeftCorner), width(width), height(height) {}


Rectangle::Rectangle(const glm::vec2 &corner1, const glm::vec2 &corner2):
    lowerLeftCorner(std::min(corner1.x, corner2.x), std::min(corner1.y, corner2.y)),
    width(std::max(corner1.x, corner2.x) - std::min(corner1.x, corner2.x)),
    height(std::max(corner1.y, corner2.y) - std::min(corner1.y, corner2.y)) {}
