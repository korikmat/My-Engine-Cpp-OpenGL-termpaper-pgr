/// @file AxesCrosshair.h
/// @brief This file contains the definition of the AxesCrosshair class.
///
/// Created by korikmat on 07.05.2024.

#ifndef PROJECT_AXESCROSSHAIR_H
#define PROJECT_AXESCROSSHAIR_H

#include <vector>
#include "Shader.h"

/// @class AxesCrosshair
/// @brief The AxesCrosshair class is used to render a 3D crosshair with axes.
/// @details This class handles the initialization and rendering of a crosshair with colored lines representing the X, Y, and Z axes.
class AxesCrosshair {
public:
    /// @brief A vector containing the vertex data for the lines of the crosshair.
    /// @details Each line consists of position and color data.
    std::vector<float> lineVertices = {
            // Positions    // Colors
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Line 1: Red
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Line 2: Green
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Line 3: Blue
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    /// @brief The Vertex Array Object (VAO) for the crosshair.
    unsigned int vao;

    /// @brief Constructs an AxesCrosshair object.
    explicit AxesCrosshair();

    /// @brief Draws the crosshair using the provided shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader);

private:
    /// @brief The Vertex Buffer Object (VBO) for the crosshair.
    unsigned int vbo_;

    /// @brief Initializes the crosshair by setting up the VAO and VBO.
    void init();
};

#endif //PROJECT_AXESCROSSHAIR_H
