#include "simulation/views/sceneVisualization.hpp"

#include <imgui.h>


SceneVisualization::SceneVisualization(const int xResolution, const int yResolution):
    framebuffer(xResolution, yResolution)
{
    glViewport(0, 0, xResolution, yResolution);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}


void SceneVisualization::Render()
{
    ImGui::Begin(WindowName());

    framebuffer.Use();
    glClear(GL_COLOR_BUFFER_BIT);

    sceneShader.Use();
    sceneShader.SetCoordinateSystem(coordinateSystem);
    chain.Render(sceneShader);
    rectanglesRenderer.Render(sceneShader);

    Framebuffer::UseDefault();

    const uint64_t textureID = framebuffer.GetColorTextureId();
    const ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Image(textureID, ImVec2{ size.x, size.y }, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    upperLeftCorner.x = vMin.x;
    upperLeftCorner.y = vMin.y;

    lowerRightCorner.x = vMax.x;
    lowerRightCorner.y = vMax.y;

    mouseIsHovering = ImGui::IsItemHovered();

    ImGui::End();
}
