#include <simulation/utils/intersections.hpp>

#include <algorithm>


float Cross(const glm::vec2& v1, const glm::vec2& v2)
{
    return v1.x * v2.y - v2.x * v1.y;
}


bool LinesSegmentsIntersects(
    const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec2 &p4
) {
    const float d1 = Cross(p4 - p3, p1 - p3);
    const float d2 = Cross(p4 - p3, p2 - p3);
    const float d3 = Cross(p2 - p1, p3 - p1);
    const float d4 = Cross(p2 - p1, p4 - p1);

    const float d12 = d1 * d2;
    const float d34 = d3 * d4;

    if (d12 > 0.f || d34 > 0.f)
        return false;

    if (d12 < 0.f && d34 < 0.f)
        return true;

    if (p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4)
        return true;

    if (std::max(p1.x, p2.x) < std::min(p3.x, p4.x) ||
        std::max(p3.x, p4.x) < std::min(p1.x, p2.x) ||
        std::max(p1.y, p2.y) < std::min(p3.y, p4.y) ||
        std::max(p3.y, p4.y) < std::min(p1.y, p2.y)
    )
        return false;

    return true;
}


bool InsideRectangle(const glm::vec2& lowerLeft, const glm::vec2& upperRight, const glm::vec2& point)
{
    return point.x >= lowerLeft.x && point.x <= upperRight.x &&
           point.y >= lowerLeft.y && point.y <= upperRight.y;
}


bool LineSegmentRectangleIntersects(const Rectangle &rectangle, const glm::vec2 &start, const glm::vec2 &end)
{
    const auto lowerLeft = rectangle.LowerLeftCorner();
    if (start.x < lowerLeft.x && end.x < lowerLeft.x)
        return false;

    if (start.y < lowerLeft.y && end.y < lowerLeft.y)
        return false;

    const auto upperRight = rectangle.UpperRightCorner();
    if (start.x > upperRight.x && end.x > upperRight.x)
        return false;

    if (start.y > upperRight.y && end.y > upperRight.y)
        return false;

    if (InsideRectangle(lowerLeft, upperRight, start) && InsideRectangle(lowerLeft, upperRight, end))
        return true;

    const auto upperLeft = rectangle.UpperLeftCorner();
    const auto lowerRight = rectangle.LowerRightCorner();

    if (LinesSegmentsIntersects(lowerLeft, upperLeft, start, end) ||
        LinesSegmentsIntersects(upperLeft, upperRight, start, end) ||
        LinesSegmentsIntersects(upperRight, lowerRight, start, end) ||
        LinesSegmentsIntersects(lowerRight, lowerLeft, start, end)
    )
        return true;

    return false;
}
