#include <simulation/views/configurationSpaceVisualization.hpp>

#include <imgui.h>


void ConfigurationSpaceVisualization::Render() const
{
    ImGui::Begin(WindowName());

    reachabilityRenderer.Render();

    ImGui::End();
}
