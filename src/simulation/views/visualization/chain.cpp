#include "simulation/views/visualization/chain.hpp"

#include "simulation/views/visualization/vertex.hpp"

#include <vector>



void Chain::Update(const PossibleChainStates& states)
{
    std::visit(
        [this] (const auto& s) { UpdateMeshes(s); },
        states
    );
}


void Chain::Render(const SceneShader& shader) const
{
    if (!firstConfigurationIsValid && !secondConfigurationIsValid)
        return;

    if (secondConfigurationIsValid)
        RenderSingleMesh(secondConfiguration, shader, glm::vec4(0.5f, 0.5f, 0.5f, 1.f));

    if (firstConfigurationIsValid)
        RenderSingleMesh(firstConfiguration, shader, glm::vec4(0.f, 0.f, 1.f, 1.f));
}


void Chain::UpdateMeshes([[maybe_unused]] const NoPossibleChainStates &states)
{
    firstConfigurationIsValid = false;
    secondConfigurationIsValid = false;
}


void Chain::UpdateMeshes(const OnePossibleChainState &state)
{
    firstConfigurationIsValid = true;
    secondConfigurationIsValid = false;

    UpdateSingleMesh(firstConfiguration, state.state);
}


void Chain::UpdateMeshes(const TwoPossibleChainStates &states)
{
    firstConfigurationIsValid = true;
    secondConfigurationIsValid = true;

    UpdateSingleMesh(firstConfiguration, states.state1);
    UpdateSingleMesh(secondConfiguration, states.state2);
}


void Chain::UpdateSingleMesh(Mesh &mesh, const ChainState &state) const
{
    const float l1 = parameters.l1;
    const float l2 = parameters.l2;

    const std::vector vertices = {
        Vertex2D(0.f, 0.f),
        Vertex2D(l1 * Cos(state.alpha), l2 * Sin(state.alpha)),
        Vertex2D(l1 * Cos(state.alpha + state.beta), l2 * Sin(state.alpha + state.beta))
    };

    const std::vector<uint32_t> indices = { 0, 1, 2 };

    mesh.Update(vertices, indices, Mesh::Type::LinesStrip, Mesh::Usage::Dynamic);
}


void Chain::RenderSingleMesh(const Mesh &mesh, const SceneShader &shader, const glm::vec4 &color) {
    shader.SetColor(color);
    mesh.Use();
    glDrawElements(mesh.GetType(), static_cast<GLsizei>(mesh.GetElementsCnt()), GL_UNSIGNED_INT, nullptr);
}
