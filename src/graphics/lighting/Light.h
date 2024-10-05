/// @file Light.h
/// @brief This file contains the definition of the Light class.
///
/// Created by korikmat on 12.05.2024.

#ifndef PROJECT_LIGHT_H
#define PROJECT_LIGHT_H

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "../models/Model.h"

class Light;

using LightPtr = std::shared_ptr<Light>;

/// @class Light
/// @brief The Light class represents a light source in the scene.
/// @details This class inherits from the Model class and adds properties specific to lighting such as color, direction, and radius.
class Light : public Model {
public:
    /// @brief The color of the light.
    glm::vec3 color;

    /// @brief The direction and angle of the light.
    glm::vec4 direction_angle;

    /// @brief Flag indicating whether the light needs to be updated.
    bool needUpdate = true;

    /// @brief The radius of the light.
    float radius = 100.0f;

    /// @brief The near plane for the light's projection.
    float near_plane = 1.0f;

    /// @brief Constructs a Light object with the specified parameters.
    /// @param ID The unique identifier for the light.
    /// @param position The position of the light in the scene. Default is (10.0, 10.0, 20.0).
    /// @param color The color of the light. Default is (1.0, 1.0, 1.0).
    /// @param direction_angle The direction and angle of the light. Default is (0.0, 0.0, 1.0, 360.0).
    Light(size_t ID, glm::vec3 position = glm::vec3(10.0, 10.0, 20.0), glm::vec3 color = glm::vec3(1.0, 1.0, 1.0), glm::vec4 direction_angle = glm::vec4(0.0, 0.0, 1.0, 360.0));
};

#endif //PROJECT_LIGHT_H
