#include <simulation/controllers/mainController.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


MainController::MainController(GLFWwindow *window):
    optionsPanel(*this),
    sceneVisualization(1280, 920),
    newRectangle(),
    newRectangleFirstCorner(0.f),
    actTarget(0.5f, 0.5f),
    configurationSpaceManager(360, 360)
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
    sceneVisualization.SetChainParameters(initParams);
    obstaclesManager.SetChainParameters(initParams);

    sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));
    UpdateConfigurationSpace();
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
    sceneVisualization.Render();
    configurationSpaceVisualization.Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void MainController::MouseClicked(const MouseButton button)
{
    mouseState.ButtonClicked(button);

    if (button == Left && sceneVisualization.IsMouseOver()) {
        actTarget = ScreenPositionToVisualizationScene(mouseState.PositionGet());
        sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));
    }

    if (button == Right && sceneVisualization.IsMouseOver()) {
        newRectangleFirstCorner = ScreenPositionToVisualizationScene(mouseState.PositionGet());

        newRectangle = Rectangle(newRectangleFirstCorner, 0.f, 0.f);
        sceneVisualization.AddRectangle(newRectangle);
        obstaclesManager.AddRectangle(newRectangle);
        sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));

    }
}


void MainController::MouseReleased(const MouseButton button)
{
    mouseState.ButtonReleased(button);

    if (button == Right && sceneVisualization.IsMouseOver())
        UpdateConfigurationSpace();
}


void MainController::MouseMoved(const float x, const float y)
{
    mouseState.Moved(x, y);

    if (mouseState.IsButtonClicked(Left) && sceneVisualization.IsMouseOver()) {
        actTarget = ScreenPositionToVisualizationScene(mouseState.PositionGet());
        sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));
    }

    if (mouseState.IsButtonClicked(Right) && sceneVisualization.IsMouseOver()) {
        const glm::vec2 newCorner = ScreenPositionToVisualizationScene(mouseState.PositionGet());

        const Rectangle updatedRectangle(newRectangleFirstCorner, newCorner);

        sceneVisualization.EditRectangle(newRectangle, updatedRectangle);
        obstaclesManager.EditRectangle(newRectangle, updatedRectangle);

        newRectangle = updatedRectangle;

        sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));
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
    sceneVisualization.SetChainParameters(params);
    obstaclesManager.SetChainParameters(params);

    sceneVisualization.UpdateChain(obstaclesManager.TryToReach(actTarget));
    UpdateConfigurationSpace();
}


glm::vec2 MainController::ScreenPositionToVisualizationScene(const glm::vec2& screenPosition) const
{
    glm::vec2 result = screenPosition - sceneVisualization.WindowCenter();
    const auto& [maxX, maxY] = sceneVisualization.GetCoordinateSystem();

    result.x /= sceneVisualization.WindowWidth() / (maxX * 2.f);
    result.y /= sceneVisualization.WindowHeight() / (maxY * 2.f);
    result.y = -result.y;

    return result;
}


void MainController::UpdateConfigurationSpace()
{
    const auto& reachability = configurationSpaceManager.CalculateReachability(obstaclesManager);
    configurationSpaceVisualization.UpdateReachability(reachability);
}
