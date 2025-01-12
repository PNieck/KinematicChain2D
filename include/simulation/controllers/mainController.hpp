#pragma once

#include "mouseState.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../views/dockingSpace.hpp"
#include "../views/optionsPanel.hpp"
#include "../views/visualization.hpp"

#include "../model/model.hpp"
#include "../model/rectangle.hpp"


class MainController {
public:
    explicit MainController(GLFWwindow* window);
    ~MainController();

    void Render();

    void MouseClicked(MouseButton button);

    void MouseReleased(const MouseButton button)
        { mouseState.ButtonReleased(button); }

    void MouseMoved(float x, float y);
    void ScrollMoved(int offset);

    [[nodiscard]]
    const ChainParameters& GetChainParameters() const
        { return visualization.GetChainParameters(); }

    void SetChainParameters(const ChainParameters& params);

private:
    MouseState mouseState;

    DockingSpace dockingSpace;
    OptionsPanel optionsPanel;
    Visualization visualization;

    Rectangle newRectangle;
    glm::vec2 newRectangleFirstCorner;

    glm::vec2 actTarget;

    Model model;

    [[nodiscard]]
    glm::vec2 ScreenPositionToVisualizationScene(const glm::vec2& screenPosition) const;
};
