#pragma once

#include "rectangle.hpp"
#include "possibleChainStates.hpp"
#include "chainParameters.hpp"

#include <vector>


class Model {
public:
    PossibleChainStates TryToReach(const glm::vec2& target) const
        { return InverseKinematics(target); }

    void SetChainParameters(const ChainParameters& params)
        { chainParameters = params; }

    void AddRectangle(const Rectangle& rectangle);

    void EditRectangle(const Rectangle& oldRectangle, const Rectangle& newRectangle);

private:
    std::vector<Rectangle> rectangles;
    ChainParameters chainParameters;

    PossibleChainStates InverseKinematics(const glm::vec2& endPoint) const;
};
