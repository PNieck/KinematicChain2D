#pragma once

#include "stdShader.hpp"


class ShaderRepository {
public:
    static ShaderRepository& GetInstance() {
        static ShaderRepository instance;
        return instance;
    }

    [[nodiscard]]
    const StdShader& GetStdShader() const
        { return stdShader; }

    ShaderRepository(const ShaderRepository&) = delete;
    ShaderRepository(ShaderRepository&&) = delete;
    ShaderRepository& operator=(const ShaderRepository&) = delete;

private:
    StdShader stdShader;

    ShaderRepository() = default;
};
