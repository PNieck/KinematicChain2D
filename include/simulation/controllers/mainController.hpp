#pragma once

#include "mouseState.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../views/dockingSpace.hpp"
#include "../views/optionsPanel.hpp"
#include "../views/visualization.hpp"

#include "../model/model.hpp"
#include "../model/rectangle.hpp"

#include <tuple>


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

private:
    MouseState mouseState;

    DockingSpace dockingSpace;
    OptionsPanel optionsPanel;
    Visualization visualization;

    Rectangle newRectangle;
    glm::vec2 newRectangleFirstCorner;

    Model model;

    [[nodiscard]]
    glm::vec2 ScreenPositionToVisualizationScene(const glm::vec2& screenPosition) const;
};
