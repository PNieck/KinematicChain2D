#include "simulation/views/visualization.hpp"

#include "imgui.h"


Visualization::Visualization(const int xResolution, const int yResolution):
    framebuffer(xResolution, yResolution)
{
    glViewport(0, 0, xResolution, yResolution);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}


void Visualization::Render() const
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
    ImGui::End();
}
