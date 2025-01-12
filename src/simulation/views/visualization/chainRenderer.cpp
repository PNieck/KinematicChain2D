#include "simulation/views/visualization/chainRenderer.hpp"

#include "simulation/views/visualization/vertex.hpp"

#include "simulation/model/kinematicChain.hpp"

#include <vector>



void ChainRenderer::Update(const PossibleChainStates& states)
{
    std::visit(
        [this] (const auto& s) { UpdateMeshes(s); },
        states
    );
}


void ChainRenderer::Render(const SceneShader& shader) const
{
    if (!firstConfigurationIsValid && !secondConfigurationIsValid)
        return;

    if (secondConfigurationIsValid)
        RenderSingleMesh(secondConfiguration, shader, glm::vec4(0.5f, 0.5f, 0.5f, 1.f));

    if (firstConfigurationIsValid)
        RenderSingleMesh(firstConfiguration, shader, glm::vec4(0.f, 0.f, 1.f, 1.f));
}


void ChainRenderer::UpdateMeshes([[maybe_unused]] const NoPossibleChainStates &states)
{
    firstConfigurationIsValid = false;
    secondConfigurationIsValid = false;
}


void ChainRenderer::UpdateMeshes(const OnePossibleChainState &state)
{
    firstConfigurationIsValid = true;
    secondConfigurationIsValid = false;

    UpdateSingleMesh(firstConfiguration, state.state);
}


void ChainRenderer::UpdateMeshes(const TwoPossibleChainStates &states)
{
    firstConfigurationIsValid = true;
    secondConfigurationIsValid = true;

    UpdateSingleMesh(firstConfiguration, states.state1);
    UpdateSingleMesh(secondConfiguration, states.state2);
}


void ChainRenderer::UpdateSingleMesh(Mesh &mesh, const ChainState &state) const
{
    const KinematicChain chain(parameters, state);

    const std::vector<Vertex2D> vertices {
        chain.GetBase(),
        chain.GetJoint(),
        chain.GetEnd()
    };

    const std::vector<uint32_t> indices = { 0, 1, 2 };

    mesh.Update(vertices, indices, Mesh::Type::LinesStrip, Mesh::Usage::Dynamic);
}


void ChainRenderer::RenderSingleMesh(const Mesh &mesh, const SceneShader &shader, const glm::vec4 &color) {
    shader.SetColor(color);
    mesh.Use();
    glDrawElements(mesh.GetType(), static_cast<GLsizei>(mesh.GetElementsCnt()), GL_UNSIGNED_INT, nullptr);
}
