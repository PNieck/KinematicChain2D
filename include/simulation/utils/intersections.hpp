#pragma once

#include "../model/rectangle.hpp"

#include <glm/vec2.hpp>



bool LinesSegmentsIntersects(const glm::vec2& start1, const glm::vec2& end1, const glm::vec2& start2, const glm::vec2& end2);


bool LineSegmentRectangleIntersects(const Rectangle& rectangle, const glm::vec2& start, const glm::vec2& end);
