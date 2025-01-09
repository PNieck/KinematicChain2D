#pragma once

#include "chainState.hpp"

#include <variant>


struct NoPossibleChainStates {};


struct OnePossibleChainState {
    ChainState state;
};


struct TwoPossibleChainStates {
    ChainState state1;
    ChainState state2;
};


using PossibleChainStates = std::variant<
    NoPossibleChainStates,
    OnePossibleChainState,
    TwoPossibleChainStates
>;
