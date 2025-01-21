#pragma once

#include <cstdint>
#include <glad/glad.h>


class Texture2D {
public:
    enum InternalFormat {
        Red32BitFloat = GL_R32F,
        Red8Bit = GL_R8UI,
        RGB8Bit = GL_RGB8
    };

    enum InputDataFormat {
        Red =  GL_RED_INTEGER,
        RedGreenBlue =  GL_RGB
    };

    explicit Texture2D(InternalFormat internalFormat);
    Texture2D(int width, int height, const float *data, InternalFormat internalFormat, InputDataFormat inputFormat);
    Texture2D(const Texture2D &texture) = delete;
    ~Texture2D();

    void Update(int texWidth, int texHeight, const float *data, InputDataFormat inputFormat);
    void Update(int texWidth, int texHeight, const uint8_t *data, InputDataFormat inputFormat);

    void Use() const
        { glBindTexture(GL_TEXTURE_2D, id); }

    [[nodiscard]]
    unsigned int Id() const
        { return id; }
private:
    unsigned int id = 0;
    InternalFormat internalFormat;
};
