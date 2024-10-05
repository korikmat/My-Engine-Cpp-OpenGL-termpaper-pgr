/// @file Mesh.h
/// @brief This file contains the definition of the Mesh class and related structures.
///
/// Created by korikmat on 30.03.2024.

#ifndef PROJECT_MESH_H
#define PROJECT_MESH_H

#include <vector>
#include <string>
#include <memory>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "../Shader.h"
#include "../Texture.h"

#define HYPNOSIS 6
#define HYPNOSIS_FRAME 24
#define FRAMES_COUNT 42
#define FRAMES_ROW 7
#define FRAMES_COLUMN 7
#define FRAMES_PERIOD_SEC 2.0f


class Mesh;

using MeshPtr = std::shared_ptr<Mesh>;

/// @struct VertexType
/// @brief Represents a vertex with position, normal, texture coordinates, tangent, and bitangent.
struct VertexType {
    glm::vec3 position; ///< The position of the vertex.
    glm::vec3 normal; ///< The normal vector of the vertex.
    glm::vec2 tex_coords; ///< The texture coordinates of the vertex.
    glm::vec3 tangent; ///< The tangent vector of the vertex.
    glm::vec3 bitangent; ///< The bitangent vector of the vertex.
};

/// @struct Materials
/// @brief Represents the material properties of a mesh.
struct Materials {
    std::string name; ///< The name of the material.
    glm::vec4 diffuse; ///< The diffuse color of the material.
    glm::vec4 specular; ///< The specular color of the material.
    float shininess; ///< The shininess coefficient of the material.
};

/// @class Mesh
/// @brief The Mesh class represents a 3D mesh with vertices, indices, textures, and materials.
/// @details This class handles the creation, rendering, and management of 3D meshes in the graphics engine.
class Mesh {
public:
    /// @brief A vector of vertices in the mesh.
    std::vector<VertexType> vertices;

    /// @brief A vector of indices for the mesh.
    std::vector<unsigned int> indices;

    /// @brief A vector of textures used by the mesh.
    std::vector<TexturePtr> textures;

    /// @brief The material properties of the mesh.
    Materials materials;

    /// @brief The number of vertices in the mesh.
    size_t verticesCount;

    /// @brief The size of a single vertex.
    size_t vertexSize;

    /// @brief Flag indicating whether the mesh has a diffuse texture.
    bool hasDiffTexture = false;

    /// @brief Flag indicating whether the mesh has a specular texture.
    bool hasSpecTexture = false;

    /// @brief The Vertex Array Object (VAO) for the mesh.
    unsigned int vao;

    /// @brief Constructs a Mesh object with the specified vertices, indices, textures, and materials.
    /// @param vertices A vector of VertexType representing the vertices of the mesh.
    /// @param indices A vector of unsigned integers representing the indices of the mesh.
    /// @param textures A vector of TexturePtr representing the textures of the mesh.
    /// @param materials The material properties of the mesh.
    Mesh(std::vector<VertexType> vertices, std::vector<unsigned int> indices, std::vector<TexturePtr> textures, Materials materials);

    /// @brief Constructs a Mesh object from a buffer and attributes.
    /// @param buffer A pointer to the vertex data buffer.
    /// @param vertices The number of vertices in the buffer.
    /// @param attrs A pointer to an array of attributes.
    Mesh(const float *buffer, size_t vertices, const int *attrs);

    /// @brief Destructor for Mesh.
    ~Mesh();

    /// @brief Draws the mesh using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader);

    /// @brief Draws the mesh as a TV screen with the specified channel ID.
    /// @param shader The shader program used for rendering.
    /// @param channelID The ID of the TV channel.
    void drawTvScreen(Shader &shader, int channelID);

    /// @brief Draws the mesh as a UI element.
    void drawUi();

    /// @brief Reloads the mesh with new vertex data.
    /// @param buffer A pointer to the new vertex data buffer.
    /// @param vertices The number of vertices in the buffer.
    void reload(const float *buffer, size_t vertices);

private:
    /// @brief The Vertex Buffer Object (VBO) for the mesh.
    unsigned int vbo_;

    /// @brief The Element Buffer Object (EBO) for the mesh.
    unsigned int ebo_;

    /// @brief Initializes the mesh by setting up the VAO, VBO, and EBO.
    void init();
};

#endif //PROJECT_MESH_H
