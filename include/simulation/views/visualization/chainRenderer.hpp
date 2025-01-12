#pragma once

#include "../../model/chainParameters.hpp"
#include "../../model/chainState.hpp"
#include "../../model/possibleChainStates.hpp"

#include "mesh.hpp"
#include "shaders/sceneShader.hpp"


class ChainRenderer {
public:
    void SetParameters(const ChainParameters& params)
        { parameters = params; }

    void Update(const PossibleChainStates& states);

    void Render(const SceneShader& shader) const;

private:
    ChainParameters parameters;

    bool firstConfigurationIsValid = true;
    Mesh firstConfiguration;

    bool secondConfigurationIsValid = true;
    Mesh secondConfiguration;

    void UpdateMeshes(const NoPossibleChainStates& states);
    void UpdateMeshes(const OnePossibleChainState& state);
    void UpdateMeshes(const TwoPossibleChainStates& states);

    void UpdateSingleMesh(Mesh& mesh, const ChainState& state) const;

    static void RenderSingleMesh(const Mesh& mesh, const SceneShader& shader, const glm::vec4& color);
};
