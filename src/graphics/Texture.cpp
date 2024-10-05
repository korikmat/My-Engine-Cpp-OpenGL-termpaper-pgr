//
// Created by korikmat on 03.03.2024.
//

#include "Texture.h"
#include "../loaders/TextureLoader.h"
#include "IL/il.h"

#include <GL/glew.h>

#include <iostream>
#include <vector>


Texture::Texture() {
    // Placeholder texture(black)
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    unsigned char blackPixel[3] = {0, 0, 0};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, blackPixel);
}

Texture::Texture(const char *path) {
    TextureLoader textureLoader;
    this->id = textureLoader.loadBasicTexture(path, &this->width, &this->height);
    if (this->id == 0) {
        std::cerr << "Failed to create texture." << std::endl;
        throw std::exception();
    }
}

Texture::Texture(std::vector<std::string> facesPaths) {
    TextureLoader textureLoader;
    this->id = textureLoader.loadSkyBoxTexture(facesPaths, &this->width, &this->height);
    if (this->id == 0) {
        std::cerr << "Failed to create texture." << std::endl;
        throw std::exception();
    }

}

Texture::Texture(unsigned char *data, int width, int height) : width(width), height(height) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::reload(unsigned char *data) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) data);
    glBindTexture(GL_TEXTURE_2D, 0);
}