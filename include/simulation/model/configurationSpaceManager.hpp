#pragma once

#include "configurationSpace.hpp"
#include "obstaclesManager.hpp"

#include <tuple>

using Bool = uint8_t;
using ChainTrajectory = std::vector<ChainState>;


class ConfigurationSpaceManager {
public:
    ConfigurationSpaceManager(size_t resolutionAlpha, size_t resolutionBeta);

    const ConfigurationSpace<Bool>& CalculateReachability(const ObstaclesManager& obstaclesManager);

    //std::tuple<ChainTrajectory, const ConfigurationSpace<float>&> FindPath(const glm::vec2& start, const glm::vec2& end, const ObstaclesManager& obstaclesManager);

private:
    ConfigurationSpace<Bool> configurationSpace;
    ConfigurationSpace<float> distanceMap;
};
