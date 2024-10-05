/// @file Batch2D.h
/// @brief This file contains the definition of the Batch2D class.
///
/// Created by korikmat.

#ifndef PROJECT_BATCH2D_H_
#define PROJECT_BATCH2D_H_

#include <stdlib.h>
#include <glm/glm.hpp>

#include "UVRegion.h"
#include "../Shader.h"

using namespace glm;

class Mesh;
class Texture;

/// @class Batch2D
/// @brief The Batch2D class is used for batching and rendering 2D sprites and textures.
/// @details This class handles the batching of vertices and their associated textures for efficient rendering.
class Batch2D {
private:
    /// @brief The buffer storing vertex data.
    float *buffer;

    /// @brief The capacity of the buffer.
    size_t capacity;

    /// @brief The current offset in the buffer.
    size_t offset;

    /// @brief The mesh used for rendering.
    Mesh *mesh;

    /// @brief The current index for batching.
    size_t index;

    /// @brief A blank texture used as a default.
    Texture *blank;

    /// @brief The current texture being used.
    Texture *_texture;

    /// @brief Adds a vertex to the buffer.
    /// @param x The x coordinate of the vertex.
    /// @param y The y coordinate of the vertex.
    /// @param u The u coordinate of the texture.
    /// @param v The v coordinate of the texture.
    /// @param r The red color component.
    /// @param g The green color component.
    /// @param b The blue color component.
    /// @param a The alpha color component.
    void vertex(float x, float y, float u, float v, float r, float g, float b, float a);

public:
    /// @brief The color to be used for rendering.
    glm::vec4 color;

    /// @brief Constructs a Batch2D object with the specified capacity.
    /// @param capacity The maximum number of vertices that can be batched.
    Batch2D(size_t capacity);

    /// @brief Destructor for Batch2D.
    ~Batch2D();

    /// @brief Begins the batching process.
    void begin();

    /// @brief Sets the texture to be used for rendering.
    /// @param texture The texture to be used.
    void texture(Texture *texture);

    /// @brief Adds a sprite to the batch.
    /// @param x The x coordinate of the sprite.
    /// @param y The y coordinate of the sprite.
    /// @param w The width of the sprite.
    /// @param h The height of the sprite.
    /// @param atlasRes The resolution of the texture atlas.
    /// @param index The index of the sprite in the texture atlas.
    /// @param tint The tint color to be applied to the sprite.
    void sprite(float x, float y, float w, float h, int atlasRes, int index, vec4 tint);

    /// @brief Adds a rectangle to the batch.
    /// @param x The x coordinate of the rectangle.
    /// @param y The y coordinate of the rectangle.
    /// @param w The width of the rectangle.
    /// @param h The height of the rectangle.
    /// @param u The u coordinate of the texture.
    /// @param v The v coordinate of the texture.
    /// @param tx The texture x coordinate.
    /// @param ty The texture y coordinate.
    /// @param r The red color component.
    /// @param g The green color component.
    /// @param b The blue color component.
    /// @param a The alpha color component.
    void rect(float x, float y, float w, float h, float u, float v, float tx, float ty, float r, float g, float b, float a);

    /// @brief Renders the batched sprites and textures.
    void render();
};

#endif /* PROJECT_BATCH2D_H_ */
