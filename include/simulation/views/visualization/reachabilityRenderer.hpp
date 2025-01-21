#pragma once

#include "texture2D.hpp"
#include "../../model/configurationSpaceManager.hpp"

#include <glm/vec3.hpp>


class ReachabilityRenderer {
public:
    ReachabilityRenderer():
        texture(Texture2D::RGB8Bit),
        textureData(360, 360) {}

    void Update(const ConfigurationSpace<Bool>& configurationSpace);

    void Render() const;

    [[nodiscard]]
    unsigned int TextureId() const
        { return texture.Id(); }
private:
    Texture2D texture;
    Vector2D<glm::vec3> textureData;
};
