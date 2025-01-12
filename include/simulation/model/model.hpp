#pragma once

#include "rectangle.hpp"
#include "possibleChainStates.hpp"
#include "chainParameters.hpp"

#include <vector>


class Model {
public:
    [[nodiscard]]
    PossibleChainStates TryToReach(const glm::vec2& target) const;

    void SetChainParameters(const ChainParameters& params)
        { chainParameters = params; }

    void AddRectangle(const Rectangle& rectangle);

    void EditRectangle(const Rectangle& oldRectangle, const Rectangle& newRectangle);

private:
    std::vector<Rectangle> rectangles;
    ChainParameters chainParameters;

    [[nodiscard]]
    PossibleChainStates InverseKinematics(const glm::vec2& endPoint) const;

    [[nodiscard]]
    PossibleChainStates CollideWithRectangles(const NoPossibleChainStates& s) const;
    [[nodiscard]]
    PossibleChainStates CollideWithRectangles(const OnePossibleChainState& s) const;
    [[nodiscard]]
    PossibleChainStates CollideWithRectangles(const TwoPossibleChainStates& s) const;

    [[nodiscard]]
    bool CollidesWithRectangles(const ChainState& state) const;
};
