#pragma once

#include "visualization/shaders/sceneShader.hpp"
#include "visualization/framebuffer.hpp"
#include "visualization/chainRenderer.hpp"
#include "visualization/rectanglesRenderer.hpp"

#include "../model/chainParameters.hpp"


class Visualization {
public:
    Visualization(int xResolution, int yResolution);

    void UpdateChain(const PossibleChainStates& states)
        { chain.Update(states); }

    void Render();

    void SetChainParameters(const ChainParameters& parameters)
        { chain.SetParameters(parameters); }

    [[nodiscard]]
    const ChainParameters& GetChainParameters() const
        { return chain.GetParameters(); };

    void AddRectangle(const Rectangle& rectangle)
        { rectanglesRenderer.AddRectangle(rectangle); }

    void EditRectangle(const Rectangle& oldRectangle, const Rectangle& newRectangle)
        { rectanglesRenderer.EditRectangle(oldRectangle, newRectangle); }

    [[nodiscard]]
    const CoordinateSystem& GetCoordinateSystem() const
        { return coordinateSystem; }

    [[nodiscard]]
    static const char* WindowName()
        { return "Visualization"; }

    [[nodiscard]]
    bool IsMouseOver() const
        { return mouseIsHovering; }

    [[nodiscard]]
    glm::vec2 UpperLeftCorner() const
        { return upperLeftCorner; }

    [[nodiscard]]
    float WindowWidth() const
        { return lowerRightCorner.x - upperLeftCorner.x; }

    [[nodiscard]]
    float WindowHeight() const
        { return lowerRightCorner.y - upperLeftCorner.y; }

    [[nodiscard]]
    glm::vec2 WindowCenter() const
        { return (upperLeftCorner + lowerRightCorner) / 2.f; }

private:
    Framebuffer framebuffer;
    SceneShader sceneShader;

    ChainRenderer chain;
    RectanglesRenderer rectanglesRenderer;
    CoordinateSystem coordinateSystem;

    glm::vec2 upperLeftCorner;
    glm::vec2 lowerRightCorner;
    bool mouseIsHovering = false;
};
