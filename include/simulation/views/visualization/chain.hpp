#pragma once

#include "../../model/chainParameters.hpp"
#include "../../model/chainState.hpp"
#include "../../model/coordinateSystem.hpp"
#include "../../model/possibleChainStates.hpp"

#include "mesh.hpp"
#include "shaders/stdShader.hpp"


class Chain {
public:
    void SetParameters(const ChainParameters& params)
        { parameters = params; }

    void SetCoordinateSystem(const CoordinateSystem& system)
        { coordinateSystem = system; }

    void Update(const PossibleChainStates& states);

    void Render() const;

private:
    ChainParameters parameters;
    ChainState actState;

    CoordinateSystem coordinateSystem;

    bool firstConfigurationIsValid = true;
    Mesh firstConfiguration;

    bool secondConfigurationIsValid = true;
    Mesh secondConfiguration;

    void UpdateMeshes(const NoPossibleChainStates& states);
    void UpdateMeshes(const OnePossibleChainState& state);
    void UpdateMeshes(const TwoPossibleChainStates& states);

    void UpdateSingleMesh(Mesh& mesh, const ChainState& state) const;

    static void RenderSingleMesh(const Mesh& mesh, const StdShader& shader, const glm::vec4& color);
};
