#include <simulation/model/rectangle.hpp>

#include <algorithm>


Rectangle::Rectangle(const glm::vec2 &lowerLeftCorner, const float width, const float height):
    lowerLeftCorner(lowerLeftCorner), width(width), height(height) {}


Rectangle::Rectangle(const glm::vec2 &corner1, const glm::vec2 &corner2):
    lowerLeftCorner(std::min(corner1.x, corner2.x), std::min(corner1.y, corner2.y)),
    width(std::max(corner1.x, corner2.x) - lowerLeftCorner.x),
    height(std::max(corner1.y, corner2.y) - lowerLeftCorner.y) {}


bool Rectangle::operator==(const Rectangle &other) const
{
    return lowerLeftCorner == other.lowerLeftCorner &&
           width == other.width &&
           height == other.height;
}