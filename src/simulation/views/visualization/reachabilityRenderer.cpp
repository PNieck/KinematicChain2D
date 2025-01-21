#include <simulation/views/visualization/reachabilityRenderer.hpp>

#include <imgui.h>


void ReachabilityRenderer::Update(const ConfigurationSpace<Bool> &configurationSpace)
{
    for (size_t alphaIndex = 0; alphaIndex < configurationSpace.AlphaResolution(); alphaIndex++) {
        for (size_t betaIndex = 0; betaIndex < configurationSpace.BetaResolution(); betaIndex++) {
            if (configurationSpace.At(alphaIndex, betaIndex) == 0)
                textureData.At(alphaIndex, betaIndex) = glm::vec3(0.0, 0.0, 0.0);
            else
                textureData.At(alphaIndex, betaIndex) = glm::vec3(1.0, 0.0, 0.0);
        }
    }

    texture.Use();
    texture.Update(
        static_cast<int>(configurationSpace.AlphaResolution()),
        static_cast<int>(configurationSpace.BetaResolution()),
        reinterpret_cast<float*>(textureData.ToVector().data()),
        Texture2D::InputDataFormat::RedGreenBlue
    );
}


void ReachabilityRenderer::Render() const
{
    const ImVec2 size = ImGui::GetContentRegionAvail();

    texture.Use();
    ImGui::Image(texture.Id(), ImVec2{ size.x, size.y }, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}
