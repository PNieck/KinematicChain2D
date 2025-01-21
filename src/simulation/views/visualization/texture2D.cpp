#include <simulation/views/visualization/texture2D.hpp>



Texture2D::Texture2D(const InternalFormat internalFormat):
    internalFormat(internalFormat)
{
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


Texture2D::Texture2D(const int width, const int height, const float *data, const InternalFormat internalFormat,
                     const InputDataFormat inputFormat):
    internalFormat(internalFormat)
{
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, inputFormat, GL_FLOAT, data);
}


void Texture2D::Update(const int texWidth, const int texHeight, const float *data, const InputDataFormat inputFormat)
{
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texWidth, texHeight, 0, inputFormat, GL_FLOAT, data);
}


void Texture2D::Update(const int texWidth, const int texHeight, const uint8_t *data, const InputDataFormat inputFormat)
{
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texWidth, texHeight, 0, inputFormat, GL_UNSIGNED_BYTE, data);
}


Texture2D::~Texture2D()
{
    glDeleteTextures(1, &id);
}
