#include <simulation/views/optionsPanel.hpp>

#include <imgui.h>

#include "simulation/controllers/mainController.hpp"


OptionsPanel::OptionsPanel(MainController &controller):
    controller(controller)
{
}


void OptionsPanel::Render() const
{
    ImGui::Begin("Options");

    RenderChainOptions();

    ImGui::End();
}


void OptionsPanel::RenderChainOptions() const
{
    ImGui::SeparatorText("Kinematic chain options");

    auto params = controller.GetChainParameters();
    bool paramsChanged = false;

    ImGui::Text("Fist section length");
    paramsChanged |= ImGui::DragFloat("##l1", &params.l1, 0.1f, 0.01f);

    ImGui::Text("Second section length");
    paramsChanged |= ImGui::DragFloat("##l2", &params.l2, 0.1f, 0.01f);

    if (paramsChanged)
        controller.SetChainParameters(params);
}



