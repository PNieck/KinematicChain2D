#pragma once

#include "../model/configurationSpace.hpp"
#include "../model/configurationSpaceManager.hpp"
#include "visualization/texture2D.hpp"

#include "visualization/reachabilityRenderer.hpp"


class ConfigurationSpaceVisualization {
public:
    void UpdateReachability(const ConfigurationSpace<Bool>& reachabilityMap)
        { reachabilityRenderer.Update(reachabilityMap); }

    void Render() const;

    [[nodiscard]]
    static const char* WindowName()
        { return "Configuration space visualization"; }

private:
    ReachabilityRenderer reachabilityRenderer;
};
