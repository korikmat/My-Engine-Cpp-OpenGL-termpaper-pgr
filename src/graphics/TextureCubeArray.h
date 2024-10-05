/// @file TextureCubeArray.h
/// @brief This file contains the definition of the TextureCubeArray class.
///
/// Created by korikmat on 12.05.2024.

#ifndef PROJECT_TEXTURECUBEARRAY_H
#define PROJECT_TEXTURECUBEARRAY_H

/// @class TextureCubeArray
/// @brief The TextureCubeArray class handles the creation and management of a texture cube array.
/// @details This class supports creating a texture cube array for shadow mapping and other purposes.
class TextureCubeArray {
public:
    /// @brief The width of each shadow map.
    const unsigned int SHADOW_WIDTH = 1024;

    /// @brief The height of each shadow map.
    const unsigned int SHADOW_HEIGHT = 1024;

    /// @brief The ID of the texture cube array.
    unsigned int textureCubeArray;

    /// @brief The ID of the framebuffer object for the depth map.
    unsigned int depthMapFBO;

    /// @brief Constructs a TextureCubeArray object with the specified number of levels.
    /// @param levels The number of levels in the texture cube array.
    TextureCubeArray(unsigned int levels);

    /// @brief Binds the texture cube array for use in rendering.
    void bind();
};

#endif //PROJECT_TEXTURECUBEARRAY_H
