/// @file TextureLoader.h
/// @brief This file contains the definition of the TextureLoader class.
///
/// Created by korikmat on 07.05.2024.

#ifndef PROJECT_TEXTURELOADER_H
#define PROJECT_TEXTURELOADER_H

#include <vector>
#include <string>
#include "GL/glew.h"

/// @class TextureLoader
/// @brief The TextureLoader class is responsible for loading textures.
/// @details This class provides methods to load 2D textures and skybox textures from files.
class TextureLoader {
public:
    /// @brief Loads a 2D texture image from a file.
    /// @param fileName The path to the texture file.
    /// @param target The target texture (e.g., GL_TEXTURE_2D).
    /// @return True if the texture was successfully loaded, false otherwise.
    bool loadTexImage2D(const char *fileName, GLenum target);

    /// @brief Creates a texture from a file and returns its OpenGL ID.
    /// @param fileName The path to the texture file.
    /// @param width Pointer to an int to store the width of the texture.
    /// @param height Pointer to an int to store the height of the texture.
    /// @return The OpenGL ID of the created texture.
    GLuint createTexture(const char *fileName, int *width, int *height);

    /// @brief Creates a skybox texture from a set of face images.
    /// @param facesPaths A vector of file paths to the skybox face images.
    /// @param width Pointer to an int to store the width of the texture.
    /// @param height Pointer to an int to store the height of the texture.
    /// @return The OpenGL ID of the created skybox texture.
    GLuint createSkyBoxTexture(const std::vector<std::string> &facesPaths, int *width, int *height);

    /// @brief Loads a basic texture from a file and returns its OpenGL ID.
    /// @param path The path to the texture file.
    /// @param width Pointer to an int to store the width of the texture.
    /// @param height Pointer to an int to store the height of the texture.
    /// @return The OpenGL ID of the loaded texture.
    unsigned int loadBasicTexture(const char *path, int *width, int *height);

    /// @brief Loads a skybox texture from a set of face images and returns its OpenGL ID.
    /// @param facesPaths A vector of file paths to the skybox face images.
    /// @param width Pointer to an int to store the width of the texture.
    /// @param height Pointer to an int to store the height of the texture.
    /// @return The OpenGL ID of the loaded skybox texture.
    unsigned int loadSkyBoxTexture(std::vector<std::string> facesPaths, int *width, int *height);

private:
    // Private methods and member variables can be added here if needed
};

#endif //PROJECT_TEXTURELOADER_H
