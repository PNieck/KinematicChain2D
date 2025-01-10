#pragma once

#include "visualization/shaders/sceneShader.hpp"
#include "visualization/framebuffer.hpp"
#include "visualization/chain.hpp"
#include "visualization/rectanglesRenderer.hpp"

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
    SceneShader sceneShader;

    Chain chain;
    RectanglesRenderer rectanglesRenderer;
    CoordinateSystem coordinateSystem;
};
