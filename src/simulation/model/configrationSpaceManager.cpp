#include <simulation/model/configurationSpaceManager.hpp>

#include <limits>
#include <ranges>
#include <algorithm>


ConfigurationSpaceManager::ConfigurationSpaceManager(const size_t resolutionAlpha, const size_t resolutionBeta):
    configurationSpace(resolutionAlpha, resolutionBeta),
    distanceMap(resolutionAlpha, resolutionBeta)
{
}


const ConfigurationSpace<Bool>& ConfigurationSpaceManager::CalculateReachability(const ObstaclesManager &obstaclesManager)
{
    if (obstaclesManager.NumberOfObstacles() == 0) {
        std::ranges::fill(configurationSpace.ToVector(), 0);
    }

    for (size_t alphaIndex = 0; alphaIndex < configurationSpace.AlphaResolution(); alphaIndex++) {
        for (size_t betaIndex = 0; betaIndex < configurationSpace.BetaResolution(); betaIndex++) {
            const ChainState state = configurationSpace.IndicesToState(alphaIndex, betaIndex);

            if (obstaclesManager.CollidesWithRectangles(state))
                configurationSpace.At(alphaIndex, betaIndex) = std::numeric_limits<Bool>::max();
            else
                configurationSpace.At(alphaIndex, betaIndex) = 0;
        }
    }

    return configurationSpace;
}


// std::tuple<ChainTrajectory, const ConfigurationSpace<float>&> ConfigurationSpaceManager::FindPath(
//     const glm::vec2 &start, const glm::vec2 &end, const ObstaclesManager &obstaclesManager)
// {
//
// }
