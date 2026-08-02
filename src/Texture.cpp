#include "Texture.hpp"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

Texture::Texture(const std::string& path)
    : _ID(0), _width(0), _height(0)
{
    loadPPM(path);
}

Texture::~Texture()
{
    if (_ID != 0)
        glDeleteTextures(1, &_ID);
}

void Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ID);
}

void Texture::loadPPM(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open texture: "
                  << path << std::endl;
        return;
    }

    std::string format;
    file >> format;

    if (format != "P6")
    {
        std::cerr << "Unsupported PPM format: "
                  << format << std::endl;
        return;
    }

    file >> _width >> _height;

    int maxValue;
    file >> maxValue;

    if (_width <= 0 || _height <= 0 || maxValue != 255)
    {
        std::cerr << "Invalid PPM texture" << std::endl;
        return;
    }

    file.get();

    std::vector<unsigned char> pixels(
        _width * _height * 3
    );

    file.read(
        reinterpret_cast<char*>(pixels.data()),
        pixels.size()
    );

    if (!file)
    {
        std::cerr << "Failed to read texture data"
                  << std::endl;
        return;
    }

    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        _width,
        _height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}
