#pragma once

#include "visualization/framebuffer.hpp"
#include "visualization/chain.hpp"

#include "../model/chainParameters.hpp"


class Visualization {
public:
    Visualization(int xResolution, int yResolution);

    void Render() const;

    void SetChainParameters(const ChainParameters& parameters)
        { chain.SetParameters(parameters); }

    [[nodiscard]]
    static const char* WindowName()
        { return "Visualization"; }

private:
    Framebuffer framebuffer;

    Chain chain;
};
