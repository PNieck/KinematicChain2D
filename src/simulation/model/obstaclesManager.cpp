#include "simulation/model/obstaclesManager.hpp"

#include "simulation/utils/intersections.hpp"
#include "simulation/model/kinematicChain.hpp"

#include <glm/glm.hpp>

#include <ranges>
#include <stdexcept>
#include <algorithm>


PossibleChainStates ObstaclesManager::TryToReach(const glm::vec2 &target) const
{
    auto states = InverseKinematics(target);

    return std::visit(
        [this] (const auto& s) { return CollideWithRectangles(s); }, states
    );
}


void ObstaclesManager::AddRectangle(const Rectangle &rectangle)
{
    rectangles.push_back(rectangle);
}


void ObstaclesManager::EditRectangle(const Rectangle &oldRectangle, const Rectangle &newRectangle)
{
    for (auto& rect : std::ranges::views::reverse(rectangles)) {
        if (rect == oldRectangle) {
            rect = newRectangle;
            return;
        }
    }

    throw std::runtime_error("Cannot find rectangle to modify");
}


PossibleChainStates ObstaclesManager::InverseKinematics(const glm::vec2 &endPoint) const
{
    const float len = length(endPoint);

    if (chainParameters.l1 + chainParameters.l2 < len)
        return NoPossibleChainStates();

    const Angle a = Atan2(endPoint.y, endPoint.x);

    if (chainParameters.l1 + chainParameters.l2 == len)
        return OnePossibleChainState(a, Angle::FromRadians(0.f));

    const float l1Squared = chainParameters.l1 * chainParameters.l1;
    const float l2Squared = chainParameters.l2 * chainParameters.l2;
    const float lenSquared = endPoint.x * endPoint.x + endPoint.y * endPoint.y;

    const Angle b = Acos((l1Squared + lenSquared - l2Squared) / (2.f * chainParameters.l1 * len));
    const Angle c = Acos((l1Squared + l2Squared - lenSquared) / (2.f * chainParameters.l1 * chainParameters.l2));

    return TwoPossibleChainStates(
        a+b, Angle::FromDegrees(180)+c,
        a-b, Angle::FromDegrees(180)-c
    );
}


PossibleChainStates ObstaclesManager::CollideWithRectangles(const NoPossibleChainStates &s) const
    { return s; }


PossibleChainStates ObstaclesManager::CollideWithRectangles(const OnePossibleChainState &s) const
{
    if (CollidesWithRectangles(s.state))
        return NoPossibleChainStates();

    return s;
}


PossibleChainStates ObstaclesManager::CollideWithRectangles(const TwoPossibleChainStates &s) const
{
    const bool firstCollides = CollidesWithRectangles(s.state1);
    const bool secondCollides = CollidesWithRectangles(s.state2);

    if (!firstCollides && !secondCollides)
        return s;

    if (!firstCollides)
        return OnePossibleChainState(s.state1);

    if (!secondCollides)
        return OnePossibleChainState(s.state2);

    return NoPossibleChainStates();
}


bool ObstaclesManager::CollidesWithRectangles(const ChainState &state) const {
    const KinematicChain chain(chainParameters, state);

    return std::ranges::any_of(rectangles, [&chain](const auto& rect) {
        return LineSegmentRectangleIntersects(rect, chain.GetBase(), chain.GetJoint()) ||
               LineSegmentRectangleIntersects(rect, chain.GetJoint(), chain.GetEnd());
    });
}
