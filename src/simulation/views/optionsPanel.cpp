#include <simulation/views/optionsPanel.hpp>

#include <imgui.h>

#include "simulation/controllers/mainController.hpp"


OptionsPanel::OptionsPanel(MainController &controller):
    controller(controller)
{
}


void OptionsPanel::Render()
{
    ImGui::Begin("Options");

    RenderStartStopButton(true);

    ImGui::End();
}


void OptionsPanel::RenderStartStopButton(const bool simRuns)
{
    ImGui::BeginDisabled(simRuns);
    if (ImGui::Button("Start")) {

    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    ImGui::BeginDisabled(!simRuns);
    if (ImGui::Button("Stop")) {

    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(simRuns);
    if (ImGui::Button("Update")) {

    }

    if (ImGui::Button("Reset")) {
    }
    ImGui::EndDisabled();
}
