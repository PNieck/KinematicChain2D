#pragma once

#include "chainParameters.hpp"
#include "chainState.hpp"

#include <glm/vec2.hpp>


class KinematicChain {
public:
    KinematicChain(const ChainParameters& params, const ChainState& state);

    const glm::vec2& GetBase() const
        { return base; }

    const glm::vec2& GetJoint() const
        { return joint; }

    const glm::vec2& GetEnd() const
        { return end; }

private:
    glm::vec2 base;
    glm::vec2 joint;
    glm::vec2 end;
};
