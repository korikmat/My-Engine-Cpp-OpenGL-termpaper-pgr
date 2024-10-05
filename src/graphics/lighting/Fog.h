/// @file Fog.h
/// @brief This file contains the definition of the Fog class.
///
/// Created by korikmat on 20.05.2024.

#ifndef PROJECT_FOG_H
#define PROJECT_FOG_H

#include "glm/vec3.hpp"

/// @class Fog
/// @brief The Fog class is used to define fog properties in a scene.
/// @details This class contains properties such as color, density, and enabled state to control the fog effect.
class Fog {
public:
    /// @brief Constructs a Fog object with default parameters.
    Fog();

    /// @brief The color of the fog.
    glm::vec3 color;

    /// @brief The density of the fog.
    float density;

    /// @brief Flag indicating whether the fog is enabled.
    bool enabled;
};

#endif //PROJECT_FOG_H
