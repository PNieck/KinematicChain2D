#include <simulation/model/kinematicChain.hpp>


KinematicChain::KinematicChain(const ChainParameters &params, const ChainState &state):
    base(0.f),
    joint(params.l1 * Cos(state.alpha), params.l1 * Sin(state.alpha)),
    end(
        joint.x + params.l2 * Cos(state.alpha + state.beta),
        joint.y + params.l2 * Sin(state.alpha + state.beta)
    ) {}
