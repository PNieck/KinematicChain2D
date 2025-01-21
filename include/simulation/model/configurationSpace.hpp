#pragma once

#include "../utils/vector2D.hpp"
#include "chainState.hpp"


template <typename T>
class ConfigurationSpace {
public:
    ConfigurationSpace(const size_t resolutionAlpha, const size_t resolutionBeta):
        data(resolutionAlpha, resolutionBeta) {}

    [[nodiscard]]
    const float& At(const size_t alphaIndex, const size_t betaIndex) const
        { return data.At(alphaIndex, betaIndex); }

    [[nodiscard]]
    T& At(const size_t alphaIndex, const size_t betaIndex)
        { return data.At(alphaIndex, betaIndex); }

    [[nodiscard]]
    ChainState IndicesToState(const size_t alphaIndex, const size_t betaIndex) const {
        return {
            Angle::FromDegrees(360) / static_cast<float>(AlphaResolution()) * static_cast<float>(alphaIndex),
            Angle::FromDegrees(360) / static_cast<float>(BetaResolution()) * static_cast<float>(betaIndex)
        };
    }


    [[nodiscard]]
    size_t AlphaResolution() const
        { return data.Columns(); }

    [[nodiscard]]
    size_t BetaResolution() const
        { return data.Rows(); }

    const std::vector<T>& ToVector() const
        { return data.ToVector(); }

    std::vector<T>& ToVector()
        { return data.ToVector(); }

private:
    Vector2D<T> data;
};
