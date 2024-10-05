/// @file SkyBox.h
/// @brief This file contains the definition of the SkyBox class.
///
/// Created by korikmat on 07.05.2024.

#ifndef PROJECT_SKYBOX_H
#define PROJECT_SKYBOX_H

#include "models/Mesh.h"
#include "Texture.h"

/// @class SkyBox
/// @brief The SkyBox class represents a skybox in the scene.
/// @details This class handles the initialization, loading, and rendering of a skybox using cube textures.
class SkyBox {
public:
    /// @brief Paths to the six faces of the skybox texture.
    std::vector<std::string> facesPaths = {
            "res/skybox/right.png",
            "res/skybox/left.png",
            "res/skybox/top.png",
            "res/skybox/bottom.png",
            "res/skybox/front.png",
            "res/skybox/back.png"
    };

    /// @brief Vertices for the skybox cube.
    std::vector<float> skyboxVertices = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
    };

    /// @brief The Vertex Array Object (VAO) for the skybox.
    unsigned int vao;

    /// @brief The texture object for the skybox.
    Texture texture;

    /// @brief Constructs a SkyBox object and initializes the skybox.
    explicit SkyBox();

    /// @brief Draws the skybox using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader);

private:
    /// @brief The Vertex Buffer Object (VBO) for the skybox.
    unsigned int vbo_;

    /// @brief Initializes the skybox by setting up the VAO and VBO.
    void init();
};

#endif //PROJECT_SKYBOX_H
