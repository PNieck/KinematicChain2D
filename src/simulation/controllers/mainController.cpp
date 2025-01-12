#include <simulation/controllers/mainController.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


MainController::MainController(GLFWwindow *window):
    optionsPanel(*this), visualization(1280, 920),
    newRectangle(),
    newRectangleFirstCorner(0.f),
    actTarget(0.5f, 0.5f)
{
    const auto glsl_version = "#version 410";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    constexpr  ChainParameters initParams;
    visualization.SetChainParameters(initParams);
    model.SetChainParameters(initParams);

    visualization.UpdateChain(model.TryToReach(actTarget));
}


MainController::~MainController()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void MainController::Render()
{
    // Creating new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    dockingSpace.Render();
    optionsPanel.Render();
    visualization.Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void MainController::MouseClicked(const MouseButton button)
{
    mouseState.ButtonClicked(button);

    if (button == Right && visualization.IsMouseOver()) {
        newRectangleFirstCorner = ScreenPositionToVisualizationScene(mouseState.PositionGet());

        newRectangle = Rectangle(newRectangleFirstCorner, 0.f, 0.f);
        visualization.AddRectangle(newRectangle);
        model.AddRectangle(newRectangle);
        visualization.UpdateChain(model.TryToReach(actTarget));
    }

    if (button == Left && visualization.IsMouseOver()) {
        actTarget = ScreenPositionToVisualizationScene(mouseState.PositionGet());
        visualization.UpdateChain(model.TryToReach(actTarget));
    }
}


void MainController::MouseMoved(const float x, const float y)
{
    mouseState.Moved(x, y);

    if (mouseState.IsButtonClicked(Right) && visualization.IsMouseOver()) {
        const glm::vec2 newCorner = ScreenPositionToVisualizationScene(mouseState.PositionGet());

        const Rectangle updatedRectangle(newRectangleFirstCorner, newCorner);

        visualization.EditRectangle(newRectangle, updatedRectangle);
        model.EditRectangle(newRectangle, updatedRectangle);

        newRectangle = updatedRectangle;

        visualization.UpdateChain(model.TryToReach(actTarget));
    }

    if (mouseState.IsButtonClicked(Left) && visualization.IsMouseOver()) {
        actTarget = ScreenPositionToVisualizationScene(mouseState.PositionGet());
        visualization.UpdateChain(model.TryToReach(actTarget));
    }
}


void MainController::ScrollMoved(const int offset)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    float val = offset * 0.7f;

    if (val < 0.0f) {
        val = -1.0f / val;
    }
}


void MainController::SetChainParameters(const ChainParameters &params)
{
    visualization.SetChainParameters(params);
    model.SetChainParameters(params);

    visualization.UpdateChain(model.TryToReach(actTarget));
}


glm::vec2 MainController::ScreenPositionToVisualizationScene(const glm::vec2& screenPosition) const
{
    glm::vec2 result = screenPosition - visualization.WindowCenter();
    const auto& [maxX, maxY] = visualization.GetCoordinateSystem();

    result.x /= visualization.WindowWidth() / (maxX * 2.f);
    result.y /= visualization.WindowHeight() / (maxY * 2.f);
    result.y = -result.y;

    return result;
}
