#include "simulation/model/model.hpp"

#include <glm/glm.hpp>


void Model::AddRectangle(const Rectangle &rectangle)
{
    rectangles.push_back(rectangle);
}


PossibleChainStates Model::InverseKinematics(const glm::vec2 &endPoint) const
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
