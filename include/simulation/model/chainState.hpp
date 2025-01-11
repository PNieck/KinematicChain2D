#pragma once

#include "../utils/angle.hpp"


struct ChainState {
    ChainState():
        alpha(Angle::FromRadians(0.f)),
        beta(Angle::FromRadians(0.f)) {}

    ChainState(const Angle alpha, const Angle beta):
        alpha(alpha), beta(beta) {}

    Angle alpha;
    Angle beta;

    bool operator==(const ChainState& other) const
        { return alpha == other.alpha && beta == other.beta; }
};
