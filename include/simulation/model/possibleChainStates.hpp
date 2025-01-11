#pragma once

#include "chainState.hpp"

#include <variant>


struct NoPossibleChainStates {};


struct OnePossibleChainState {
    OnePossibleChainState(const Angle alpha, const Angle beta):
        state(alpha, beta) {}

    ChainState state;
};


struct TwoPossibleChainStates {
    TwoPossibleChainStates(const Angle alpha1, const Angle beta1, const Angle alpha2, const Angle beta2):
        state1(alpha1, beta1), state2(alpha2, beta2) {}

    ChainState state1;
    ChainState state2;
};


using PossibleChainStates = std::variant<
    NoPossibleChainStates,
    OnePossibleChainState,
    TwoPossibleChainStates
>;
