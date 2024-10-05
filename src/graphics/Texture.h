/// @file Texture.h
/// @brief This file contains the definition of the Texture class.
///
/// Created by korikmat on 03.03.2024.

#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include <string>
#include <vector>
#include <memory>

class Texture;

using TexturePtr = std::shared_ptr<Texture>;

/// @class Texture
/// @brief The Texture class handles loading, binding, and managing textures.
/// @details This class supports loading textures from files, creating textures from raw data, and managing texture properties.
class Texture {
public:
    /// @brief The ID of the texture.
    unsigned int id;

    /// @brief The type of the texture (e.g., diffuse, specular).
    std::string type;

    /// @brief The file path to the texture.
    std::string path;

    /// @brief The width of the texture.
    int width;

    /// @brief The height of the texture.
    int height;

    /// @brief Constructs an empty Texture object.
    explicit Texture();

    /// @brief Constructs a Texture object from a file path.
    /// @param path The file path to the texture.
    explicit Texture(const char *path);

    /// @brief Constructs a Texture object from a vector of file paths (used for cubemaps).
    /// @param facesPaths A vector of file paths to the texture faces.
    explicit Texture(std::vector<std::string> facesPaths);

    /// @brief Constructs a Texture object from raw data.
    /// @param data A pointer to the raw texture data.
    /// @param width The width of the texture.
    /// @param height The height of the texture.
    explicit Texture(unsigned char *data, int width, int height);

    /// @brief Destructor for Texture.
    ~Texture();

    /// @brief Binds the texture for use in rendering.
    void bind() const;

    /// @brief Unbinds the texture.
    void unbind() const;

    /// @brief Reloads the texture with new data.
    /// @param data A pointer to the new raw texture data.
    void reload(unsigned char *data);
};

#endif //PROJECT_TEXTURE_H
