#pragma once

#include "mouseState.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "simulation/views/dockingSpace.hpp"
#include "simulation/views/optionsPanel.hpp"
#include "simulation/views/sceneVisualization.hpp"
#include "simulation/views/configurationSpaceVisualization.hpp"

#include "simulation/model/obstaclesManager.hpp"
#include "simulation/model/configurationSpaceManager.hpp"
#include "simulation/model/rectangle.hpp"


class MainController {
public:
    explicit MainController(GLFWwindow* window);
    ~MainController();

    void Render();

    void MouseClicked(MouseButton button);

    void MouseReleased(MouseButton button);

    void MouseMoved(float x, float y);
    void ScrollMoved(int offset);

    [[nodiscard]]
    const ChainParameters& GetChainParameters() const
        { return sceneVisualization.GetChainParameters(); }

    void SetChainParameters(const ChainParameters& params);

private:
    MouseState mouseState;

    DockingSpace dockingSpace;
    OptionsPanel optionsPanel;
    SceneVisualization sceneVisualization;
    ConfigurationSpaceVisualization configurationSpaceVisualization;

    Rectangle newRectangle;
    glm::vec2 newRectangleFirstCorner;

    glm::vec2 actTarget;

    ObstaclesManager obstaclesManager;
    ConfigurationSpaceManager configurationSpaceManager;

    [[nodiscard]]
    glm::vec2 ScreenPositionToVisualizationScene(const glm::vec2& screenPosition) const;

    void UpdateConfigurationSpace();
};
